import pako from 'https://chrweave.github.io/noodlings/pako.min.js'

class RC4Generator {
    constructor() {
        this.S = new Uint8Array(256);   
    }
    nextByte() {
        this.i = (this.i + 1) % 256;
        this.j = (this.j + this.S[this.i]) % 256;
        [this.S[this.i], this.S[this.j]] = [this.S[this.j], this.S[this.i]];
        return this.S[(this.S[this.i] + this.S[this.j]) % 256];
    }
    seed(key){
        this.i = 0;
        this.j = 0;
        this.key = new TextEncoder().encode(key);
        this.keyLength = this.key.length;
        for (let k = 0; k < 256; k++) {
            this.S[k] = k;
        }
        for(let k=0; k<this.keyLength; k++){
            this.j+=this.key[k];
            this.nextByte();
        }
        for (let i = 0; i < 2048; i++) {
            this.nextByte();
        }
    }

    pseudo_random_float(){
        var a=this.nextByte();
        a=(a<<8)+this.nextByte();
        a=(a<<8)+this.nextByte();
        return ((a<<8)+this.nextByte())/(1<<32);
    }
}

async function loadFileContent(filePath) {
    try {
        const response = await fetch(filePath);
        if (!response.ok) {
            alert("Failed to load file: " + filePath);
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        const fileContent = await response.text(); // or .json() for JSON files, .blob() for binary data
        const binaryString = atob(fileContent);
        const len = binaryString.length;
        const bytes = new Uint8Array(len);
        for (let i = 0; i < len; i++) {
            bytes[i] = binaryString.charCodeAt(i);
        }
        // Inflate (gunzip). Use a library like pako:
        const raw = pako.inflate(bytes);

        // Convert to Uint16Array
        const levelArray = new Uint16Array(raw.buffer);
        return levelArray;
    } catch (error) {
        console.error('Error loading file:', error);
        return null;
    }
}

/* ---------- FFT core from before (radix-2, in-place) ---------- */
function bitReverseIndices(N) {
    const nbits = Math.log2(N) | 0;
    const rev = new Uint32Array(N);
    for (let i = 0; i < N; i++) {
        let x = i, y = 0;
        for (let b = 0; b < nbits; b++) { y = (y << 1) | (x & 1); x >>>= 1; }
        rev[i] = y;
    }
    return rev;
}

function fft_inplace(data, inverse = false, revCache = null) {
    const N = data.length >> 1;
    if ((N & (N - 1)) !== 0) throw new Error("N must be power of two");
    const rev = revCache || bitReverseIndices(N);
    for (let i = 0; i < N; i++) {
        const j = rev[i];
        if (j > i) {
            const iRe = 2 * i, iIm = iRe + 1, jRe = 2 * j, jIm = jRe + 1;
            let tmp = data[iRe]; data[iRe] = data[jRe]; data[jRe] = tmp;
            tmp = data[iIm]; data[iIm] = data[jIm]; data[jIm] = tmp;
        }
    }
    const sign = inverse ? +1 : -1;
    for (let len = 2; len <= N; len <<= 1) {
        const halfLen = len >>> 1;
        const theta = sign * 2 * Math.PI / len;
        const cosStep = Math.cos(theta), sinStep = Math.sin(theta);
        for (let blockStart = 0; blockStart < N; blockStart += len) {
            let wRe = 1, wIm = 0;
            for (let j = 0; j < halfLen; j++) {
                const evenIndex = 2 * (blockStart + j);
                const oddIndex = 2 * (blockStart + j + halfLen);
                const evenRe = data[evenIndex], evenIm = data[evenIndex + 1];
                const oddRe = data[oddIndex], oddIm = data[oddIndex + 1];
                const tRe = wRe * oddRe - wIm * oddIm;
                const tIm = wRe * oddIm + wIm * oddRe;
                data[evenIndex] = evenRe + tRe;
                data[evenIndex + 1] = evenIm + tIm;
                data[oddIndex] = evenRe - tRe;
                data[oddIndex + 1] = evenIm - tIm;
                const nWRe = wRe * cosStep - wIm * sinStep;
                const nWIm = wRe * sinStep + wIm * cosStep;
                wRe = nWRe; wIm = nWIm;
            }
        }
    }
}

/* ---------- Gaussian circular convolution ---------- */
function circularGaussianConvolve(x, sigma) {
    const N = x.length; // must be power of two
    const revCache = bitReverseIndices(N);

    // 1. FFT of input
    const X = new Float64Array(2 * N);
    for (let i = 0; i < N; i++) { X[2 * i] = x[i]; X[2 * i + 1] = 0; }
    fft_inplace(X, false, revCache);

    // 2. FFT of Gaussian kernel of same length (wrapped)
    const g = new Float64Array(N);
    const sigma_squared = sigma * sigma;
    for (let i = 0; i < N; i++) {
        // shortest wrapped distance from i to 0
        let d = i;
        if (d > N / 2) d = N - d;
        g[i] = Math.exp(-(d * d) / sigma_squared);
    }
    // normalise so that sum g = 1
    let sum = 0; for (let i = 0; i < N; i++) sum += g[i];
    for (let i = 0; i < N; i++) g[i] /= sum;

    const G = new Float64Array(2 * N);
    for (let i = 0; i < N; i++) { G[2 * i] = g[i]; G[2 * i + 1] = 0; }
    fft_inplace(G, false, revCache);

    // 3. Multiply spectra: X *= G
    for (let i = 0; i < 2 * N; i += 2) {
        const aRe = X[i], aIm = X[i + 1];
        const bRe = G[i], bIm = G[i + 1];
        X[i] = aRe * bRe - aIm * bIm;
        X[i + 1] = aRe * bIm + aIm * bRe;
    }

    // 4. Inverse FFT and scale
    fft_inplace(X, true, revCache);
    const y = new Float64Array(N);
    for (let i = 0; i < N; i++) y[i] = X[2 * i] / N;
    return y;
}

function ivize(x){
    let min=1e30;
    let max=-1e30;
    for (let i=0;i<x.length;i++){
        if(x[i]<min) min=x[i];
        if(x[i]>max) max=x[i];  
    }
    var scale=1/(max-min);
    var tweak=0;
    const lightness=document.getElementById("lightness");
    if(lightness.checked){
        scale=scale*191.5;
        tweak=64;
    } 
    else {
        scale=scale*255.5
    }
    const y=new Uint8Array(x.length);  
    for (let i=0;i<x.length;i++){
        let v=(x[i]-min)*scale+tweak;
        y[i]=Math.floor(v)|0;
    }
    y[0]=0; // ensure 0 is mapped to 0
    return y;
}

function coarse_top_heavy(){
    const inv=new Float64Array(16384);
    for(let i=0;i<16384;i++){
        let v=rc4g.pseudo_random_float();
        inv[i] = 1-v*v*v;
    }
    return inv;
}

function smooth_top_heavy(inv){            
    const convolved= circularGaussianConvolve(inv, 400);// smooth with sigma=400
    return ivize(convolved);
}

function gaussianKernel(x, sigma=1.0) {
    // abs distance
    x = Math.abs(x);
    // standard gaussian
    return Math.exp(-0.5*(x*x)/(sigma*sigma));
}


function iresize(srcImageData, destWidth, destHeight, kernel, support=2) {
    const srcWidth = srcImageData.width;
    const srcHeight = srcImageData.height;
    const srcData = srcImageData.data;
    const tmp = new Float32Array(destWidth*srcHeight*4);
    const dstData = new Uint8ClampedArray(destWidth*destHeight*4);

    // horizontal pass
    for (let y=0; y<srcHeight; y++) {
        for (let dx=0; dx<destWidth; dx++) {
        const srcX = (dx+0.5)*srcWidth/destWidth - 0.5;
        const x0 = Math.floor(srcX - support + 1);
        const x1 = Math.floor(srcX + support);
        let r=0,g=0,b=0,a=0,wsum=0;
        for (let sx=x0; sx<=x1; sx++) {
            if (sx<0 || sx>=srcWidth) continue;
            const w = kernel(srcX-sx);
            const idx = (y*srcWidth + sx)*4;
            r += srcData[idx]*w;
            g += srcData[idx+1]*w;
            b += srcData[idx+2]*w;
            a += srcData[idx+3]*w;
            wsum += w;
        }
        const outIdx = (y*destWidth + dx)*4;
        tmp[outIdx]=r/wsum;
        tmp[outIdx+1]=g/wsum;
        tmp[outIdx+2]=b/wsum;
        tmp[outIdx+3]=a/wsum;
        }
    }

    // vertical pass
    for (let dy=0; dy<destHeight; dy++) {
        const srcY = (dy+0.5)*srcHeight/destHeight - 0.5;
        const y0 = Math.floor(srcY - support + 1);
        const y1 = Math.floor(srcY + support);
        for (let dx=0; dx<destWidth; dx++) {
        let r=0,g=0,b=0,a=0,wsum=0;
        for (let sy=y0; sy<=y1; sy++) {
            if (sy<0 || sy>=srcHeight) continue;
            const w = kernel(srcY-sy);
            const idx = (sy*destWidth + dx)*4;
            r += tmp[idx]*w;
            g += tmp[idx+1]*w;
            b += tmp[idx+2]*w;
            a += tmp[idx+3]*w;
            wsum += w;
        }
        const outIdx = (dy*destWidth + dx)*4;
        dstData[outIdx]=r/wsum;
        dstData[outIdx+1]=g/wsum;
        dstData[outIdx+2]=b/wsum;
        dstData[outIdx+3]=a/wsum;
        }
    }

    return new ImageData(dstData, destWidth, destHeight);
}



function color_by_levels(inlev){
    smooth_R=smooth_top_heavy(coarse_R);
    smooth_G=smooth_top_heavy(coarse_G);
    smooth_B=smooth_top_heavy(coarse_B);
    const canvas = document.createElement('canvas');
    canvas.width = width;   
    canvas.height = height;
    const ctx = canvas.getContext('2d');
    const imageData = ctx.createImageData(width, height);
    for (let y = 0; y < height; y++) {
        for (let x = 0; x < width; x++) {
                const idx = y * width + x;
            const cell = inlev[idx];
            const pixelIndex = idx * 4;
            imageData.data[pixelIndex] = smooth_R[cell]; // Red channel
            imageData.data[pixelIndex + 1] = smooth_G[cell]; // Green channel
            imageData.data[pixelIndex + 2] = smooth_B[cell];
            imageData.data[pixelIndex + 3] = 255; // Alpha channel
        }
    }
    smallCanvas = document.createElement('canvas');
    smallCanvas.width = 768;    
    smallCanvas.height = 768;
    const smallCtx = smallCanvas.getContext('2d'); 
    smallCtx.putImageData(iresize(imageData, 768, 768, (x)=>gaussianKernel(x,1), 2),0,0)
    img.src = smallCanvas.toDataURL();
}


const myhead=document.createElement("head");
const meta=document.createElement("meta");
meta.setAttribute("charset","utf-8");
myhead.appendChild(meta);
const title=document.createElement("title");
title.textContent=title_content;
myhead.appendChild(title);
const style=document.createElement("style");
style.textContent=`
body {
        font-family: sans-serif;
        font-weight: normal;
        font-style: normal;
        background-color: #f4f4f4;
        margin: 0;
        padding: 20px;
    }   
h1 {
        color: #2686f5;
}   
.my-div {           
    max-width: 800px;
    margin: 0 auto; /* Centers the div */
    font-size: 1.2rem;
    hyphens: auto;
    text-align: justify;
    text-justify: inter-word;
        /* Add other styles as needed */
}`;
myhead.appendChild(style);
document.head.replaceWith(myhead);  
const mybody=document.getElementsByTagName("body")[0];
const mydiv=document.createElement("div");
mydiv.setAttribute("class","my-div");
const main_heading=document.createElement('h1');
main_heading.textContent=title_content;
mydiv.appendChild(main_heading);
const form = document.createElement('form');
const phrase_label=document.createElement('label');
phrase_label.textContent="Input a phrase to color the Labyrinth.";
phrase_label.setAttribute("for","phrase");
form.appendChild(phrase_label);
const phrase_input=document.createElement('input');
phrase_input.setAttribute("id","phrase");   
phrase_input.setAttribute("type","text");
phrase_input.setAttribute("name","phrase");
form.appendChild(phrase_input);
const submit_input=document.createElement('input'); 
submit_input.setAttribute("type","submit");
form.appendChild(submit_input); 
form.appendChild(document.createElement("br"));
const lightness_label=document.createElement('label');  
lightness_label.textContent="Lightness?";
form.appendChild(lightness_label);  
const lightness_input=document.createElement('input');
lightness_input.setAttribute("type","checkbox");
lightness_input.setAttribute("id","lightness");
form.appendChild(lightness_input);
mydiv.appendChild(form);
const img = document.createElement("img");
const img_label=document.createElement('label');
img.setAttribute("src",uncolored_labyrinth);
mydiv.appendChild(img);
img_label.innerHTML=cc_label;
mydiv.appendChild(img_label);
mybody.appendChild(mydiv);

const rc4g = new RC4Generator();
levels=loadFileContent(b64_uri);
const width = 2048, height = 2048;
var coarse_R=[]
var coarse_G=[]
var coarse_B=[]
form.addEventListener('submit', function(event) {
    event.preventDefault(); // Prevent the form from submitting normally
    const phrase = form.phrase.value; // Get the value of the input field
    rc4g.seed(phrase);
    levels.then(levelArray => {
        coarse_R=coarse_top_heavy();
        coarse_G=coarse_top_heavy();
        coarse_B=coarse_top_heavy();
        color_by_levels(levelArray);
    });
    
});
lightness_input.addEventListener('change',function(event){
    levels.then(levelArray => {
        if (coarse_R.length >= 0){
            color_by_levels(levelArray);
        }
    })
});

function instantiate_labyrinth(levels_path,img_path,title_text){
    rc4g.seed("default");
    levels.then(levelArray => {
        coarse_R=coarse_top_heavy();
        coarse_G=coarse_top_heavy();
        coarse_B=coarse_top_heavy();
        color_by_levels(levelArray);
    });
    img.setAttribute("src",img_path);
    main_heading.textContent=title_text;

}
