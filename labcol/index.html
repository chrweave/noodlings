<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Gilwell Gazette Labyrinth Colorizer</title>
    <style>
        :root { --bg: #f4f6f8; --sidebar: #ffffff; --accent: #2c3e50; --border: #cbd5e1; }
        body { font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif; background: var(--bg); margin: 0; padding: 20px; display: flex; flex-direction: column; align-items: center; min-height: 100vh; }
        .header { text-align: center; margin-bottom: 20px; color: var(--accent); }
        .header h1 { margin: 0 0 5px 0; font-size: 1.8em; letter-spacing: 0.5px; }
        .header p { margin: 0; color: #64748b; font-size: 0.9em; }
        
        #workspace { display: flex; gap: 20px; background: var(--sidebar); padding: 20px; border-radius: 8px; box-shadow: 0 4px 6px rgba(0,0,0,0.05); max-width: 1200px; width: 100%; align-items: flex-start; }
        
        #left-col { flex: 1; display: flex; flex-direction: column; align-items: center; }
        .canvas-container { position: relative; border: 2px solid var(--border); border-radius: 4px; background: #fff; overflow: hidden; }
        canvas { display: block; cursor: crosshair; image-rendering: pixelated; }
        
        #sidebar { width: 300px; display: flex; flex-direction: column; gap: 20px; }
        .panel { background: #f8fafc; border: 1px solid var(--border); padding: 15px; border-radius: 6px; }
        .panel h3 { margin: 0 0 10px 0; font-size: 1em; color: var(--accent); text-transform: uppercase; letter-spacing: 0.5px; }
        
        #gallery { display: flex; gap: 10px; overflow-x: auto; padding-bottom: 5px; }
        .thumb { width: 60px; height: 60px; object-fit: contain; cursor: pointer; border: 2px solid var(--border); background: white; border-radius: 4px; transition: 0.2s; }
        .thumb:hover { border-color: #94a3b8; }
        .thumb.selected { border-color: #3b82f6; border-width: 3px; }

        .file-upload { display: block; width: 100%; padding: 8px; margin-top: 10px; text-align: center; background: #e2e8f0; border: 2px dashed #94a3b8; border-radius: 4px; cursor: pointer; color: #475569; font-size: 0.9em; font-weight: 500; transition: 0.2s; box-sizing: border-box; }
        .file-upload:hover { background: #cbd5e1; border-color: #64748b; }
        input[type="file"] { display: none; }

        .control-row { display: flex; justify-content: space-between; align-items: center; margin-bottom: 10px; }
        input[type="color"] { cursor: pointer; width: 40px; height: 30px; padding: 0; border: 1px solid var(--border); border-radius: 4px; }
        
        button.primary { width: 100%; padding: 12px; background: var(--accent); color: white; border: none; border-radius: 4px; font-weight: bold; font-size: 1em; cursor: pointer; transition: 0.2s; }
        button.primary:hover { background: #1a252f; }
        
        .instructions { font-size: 0.85em; color: #64748b; line-height: 1.5; margin: 0; padding-left: 20px; }
        .status { font-family: monospace; padding: 8px; background: #e2e8f0; border-radius: 4px; font-size: 0.9em; color: #0f172a; text-align: center; }
        
        #finalizedDiv { margin-top: 20px; width: 100%; text-align: center; }
        #finalImg { border: 1px solid var(--border); border-radius: 4px; max-width: 100%; display: block; margin: 0 auto 10px auto; }
        .download-btn { display: inline-block; padding: 10px 20px; background: #10b981; color: white; text-decoration: none; border-radius: 4px; font-weight: bold; transition: 0.2s; }
        .download-btn:hover { background: #059669; }
    </style>
</head>
<body>

    <div class="header">
        <h1>Gazette Colorizer</h1>
        <p>Rust FMM Engine • 18th-Century Woodcut Output</p>
    </div>

    <div id="workspace">
        <div id="left-col">
            <div class="canvas-container">
                <canvas id="mainCanvas"></canvas>
            </div>
            
            <div id="finalizedDiv" style="display: none;">
                <h3 style="color: var(--accent);">Tracing Master Generated (768x768):</h3>
                <img id="finalImg">
                <a id="downloadLink" class="download-btn">Download PNG</a>
            </div>
        </div>

        <div id="sidebar">
            <div class="panel">
                <h3>1. Select Labyrinth</h3>
                <div id="gallery"></div>
                <label class="file-upload">
                    Or Upload Custom SVG
                    <input type="file" id="filePicker" accept=".svg">
                </label>
                <div id="statusOutput" class="status" style="margin-top: 10px;">Initializing WASM...</div>
            </div>

            <div class="panel" id="colorPanel" style="opacity: 0.5; pointer-events: none;">
                <h3>2. Tune Gradients</h3>
                <div class="control-row">
                    <span style="font-weight: 500; color: #475569;">Selected Node:</span>
                    <input type="color" id="colorPicker" value="#000000">
                </div>
                <ul class="instructions">
                    <li><strong>Click empty space:</strong> Add node</li>
                    <li><strong>Drag node:</strong> Move/Change flow level</li>
                    <li><strong>Select + Del:</strong> Remove node</li>
                    <li><strong>Esc:</strong> Deselect active node</li>
                </ul>
            </div>

            <button id="finalizeBtn" class="primary" style="opacity: 0.5; pointer-events: none;">3. Finalize for Tracing</button>
        </div>
    </div>

<script type="module">
    import init, { compute_fmm } from './pkg/labcol.js';

    // Added the new Chartres-style labyrinth
    const LABYRINTHS = ['wlab.svg', 'hl.svg', 'ModernChartresStyleLabyrinth.svg'];
    const WIDTH = 2048, HEIGHT = 2048, DISPLAY = 768;
    
    const canvas = document.getElementById('mainCanvas');
    const ctx = canvas.getContext('2d');
    canvas.width = DISPLAY; canvas.height = DISPLAY;

    const statusOutput = document.getElementById('statusOutput');
    const colorPicker = document.getElementById('colorPicker');
    const finalizeBtn = document.getElementById('finalizeBtn');
    const colorPanel = document.getElementById('colorPanel');
    const gallery = document.getElementById('gallery');
    const filePicker = document.getElementById('filePicker');

    let u16Data = null, paletteRGBA = null, controlPoints = [], selected = null, dragging = null;
    let currentFileName = "woodcut";

    // --- Boot Sequence ---
    async function start() {
        try {
            await init();
            statusOutput.textContent = "WASM Ready. Select a file.";
            setupGallery();
        } catch (e) {
            statusOutput.textContent = "Error loading WebAssembly.";
            console.error(e);
        }
    }

    function setupGallery() {
        LABYRINTHS.forEach(file => {
            const img = document.createElement('img');
            img.src = file;
            img.className = 'thumb';
            img.title = file;
            img.onclick = () => loadLabyrinth(file, img);
            gallery.appendChild(img);
        });
    }

    // --- Processing Pipeline ---
    async function loadLabyrinth(source, thumbElement = null, isUpload = false) {
        if (thumbElement) {
            document.querySelectorAll('.thumb').forEach(t => t.classList.remove('selected'));
            thumbElement.classList.add('selected');
        }
        
        statusOutput.textContent = "Solving Eikonal Flow...";
        document.getElementById('finalizedDiv').style.display = 'none';

        const img = new Image();
        img.src = source;
        await img.decode();

        const off = document.createElement('canvas');
        off.width = WIDTH; off.height = HEIGHT;
        const oCtx = off.getContext('2d');
        oCtx.fillStyle = "white"; 
        oCtx.fillRect(0, 0, WIDTH, HEIGHT);
        oCtx.drawImage(img, 0, 0, WIDTH, HEIGHT);

        const pixels = oCtx.getImageData(0, 0, WIDTH, HEIGHT).data;
        const walls = new Uint8Array(WIDTH * HEIGHT);
        for(let i=0; i<walls.length; i++) walls[i] = pixels[i*4] < 128 ? 0 : 1;

        // Yield to let UI update before blocking WASM call
        setTimeout(() => {
            const t0 = performance.now();
            
            // Call the Rust Eikonal Solver
            u16Data = compute_fmm(WIDTH, HEIGHT, walls, 1024, 1024);
            
            // Clean 18th-century woodcut default settings
            controlPoints = [
                { x: DISPLAY/2, y: DISPLAY/2, level: 0, color: [0,0,0,255] },
                { x: DISPLAY/2 + 40, y: DISPLAY/2 + 40, level: 2500, color: [255,255,255,255] }
            ];
            
            recomputePalette();
            
            statusOutput.textContent = `Solved in ${(performance.now()-t0).toFixed(0)}ms`;
            colorPanel.style.opacity = 1; colorPanel.style.pointerEvents = 'auto';
            finalizeBtn.style.opacity = 1; finalizeBtn.style.pointerEvents = 'auto';
        }, 50);
    }

    filePicker.addEventListener('change', (e) => {
        const file = e.target.files[0];
        if (!file) return;
        currentFileName = file.name.replace('.svg', '');
        document.querySelectorAll('.thumb').forEach(t => t.classList.remove('selected'));
        
        const reader = new FileReader();
        reader.onload = (event) => loadLabyrinth(event.target.result, null, true);
        reader.readAsDataURL(file);
    });

    // --- Palette Math ---
    function packRGBA(r, g, b, a) { return (a << 24) | (b << 16) | (g << 8) | r; }
    function unpackHex(h) { h = h.replace('#',''); return [parseInt(h.slice(0,2),16), parseInt(h.slice(2,4),16), parseInt(h.slice(4,6),16), 255]; }
    function toHex(c) { return "#" + [0,1,2].map(i => c[i].toString(16).padStart(2,'0')).join(''); }
    function sineInterp(a, b, t) { return a + (b - a) * (0.5 - 0.5 * Math.cos(t * Math.PI)); }

    function makePalette(knots) {
        const out = new Uint32Array(65536);
        out.fill(packRGBA(255,255,255,255));
        out[0] = packRGBA(0,0,0,255);
        if (knots.length === 0) return out;
        
        knots.sort((a,b) => a.level - b.level);
        const first = knots[0].level > 0 ? knots[0] : { level: 0, color: [0,0,0,255] };
        for(let i=1; i<first.level; i++) out[i] = packRGBA(...first.color);
        
        const lastColor = knots[knots.length-1].color;
        for(let i=knots[knots.length-1].level; i<65536; i++) out[i] = packRGBA(...lastColor);

        for(let k=0; k<knots.length-1; k++) {
            const a = knots[k], b = knots[k+1], len = b.level - a.level;
            if(len <= 0) continue;
            for(let i=0; i<=len; i++) {
                const t = i/len;
                out[a.level + i] = packRGBA(
                    Math.round(sineInterp(a.color[0], b.color[0], t)),
                    Math.round(sineInterp(a.color[1], b.color[1], t)),
                    Math.round(sineInterp(a.color[2], b.color[2], t)), 255
                );
            }
        }
        out[0] = packRGBA(0,0,0,255);
        return out;
    }

    function recomputePalette() { paletteRGBA = makePalette(controlPoints); draw(); }

    function draw(withUI = true) {
        if(!u16Data) return;
        if(!window.offC) {
            window.offC = document.createElement('canvas'); 
            window.offC.width = WIDTH; window.offC.height = HEIGHT;
            window.offCtx = offC.getContext('2d');
            window.offImg = offCtx.createImageData(WIDTH, HEIGHT);
            window.u32 = new Uint32Array(offImg.data.buffer);
        }
        const u32 = window.u32;
        for(let i=0; i<u16Data.length; i++) u32[i] = paletteRGBA[u16Data[i]];
        offCtx.putImageData(offImg, 0, 0);
        ctx.drawImage(offC, 0, 0, WIDTH, HEIGHT, 0, 0, DISPLAY, DISPLAY);

        if(withUI) {
            ctx.save();
            ctx.scale(DISPLAY/WIDTH, DISPLAY/HEIGHT);
            controlPoints.forEach(pt => {
                ctx.beginPath(); ctx.arc(pt.x, pt.y, 25, 0, 7);
                ctx.fillStyle = `rgba(${pt.color[0]},${pt.color[1]},${pt.color[2]},0.9)`;
                ctx.fill();
                ctx.lineWidth = (pt === selected) ? 8 : 4;
                ctx.strokeStyle = (pt === selected) ? "#3498db" : "#0f172a";
                ctx.stroke();
            });
            ctx.restore();
        }
    }

    // --- Interaction ---
    canvas.addEventListener('mousedown', e => {
        const r = canvas.getBoundingClientRect(), mx = (e.clientX-r.left)*(WIDTH/DISPLAY), my = (e.clientY-r.top)*(HEIGHT/DISPLAY);
        selected = controlPoints.find(p => Math.hypot(p.x-mx, p.y-my) < 40);
        if(selected) colorPicker.value = toHex(selected.color);
        dragging = selected; draw();
    });

    canvas.addEventListener('mousemove', e => {
        if(!dragging) return;
        const r = canvas.getBoundingClientRect();
        dragging.x = (e.clientX-r.left)*(WIDTH/DISPLAY); dragging.y = (e.clientY-r.top)*(HEIGHT/DISPLAY);
        dragging.level = u16Data[Math.floor(dragging.y)*WIDTH + Math.floor(dragging.x)];
        recomputePalette();
    });

    window.addEventListener('mouseup', () => dragging = null);

    canvas.addEventListener('click', e => {
        if(dragging) return;
        const r = canvas.getBoundingClientRect(), mx = (e.clientX-r.left)*(WIDTH/DISPLAY), my = (e.clientY-r.top)*(HEIGHT/DISPLAY);
        if(controlPoints.some(p => Math.hypot(p.x-mx, p.y-my) < 50)) return;
        controlPoints.push({ x: mx, y: my, level: u16Data[Math.floor(my)*WIDTH + Math.floor(mx)], color: unpackHex(colorPicker.value) });
        recomputePalette();
    });

    document.addEventListener('keydown', e => {
        if(e.key === 'Delete' && selected) { controlPoints = controlPoints.filter(p => p !== selected); selected = null; recomputePalette(); }
        if(e.key === 'Escape') { selected = null; draw(); }
    });

    colorPicker.addEventListener('input', () => {
        if (selected) { selected.color = unpackHex(colorPicker.value); recomputePalette(); }
    });

    // --- Finalize: Blur & 768px Downsample ---
    finalizeBtn.addEventListener('click', () => {
        if (!u16Data) return;
        
        // Grab filename from gallery selection if not uploaded
        const activeThumb = document.querySelector('.thumb.selected');
        if (activeThumb) currentFileName = activeThumb.title.replace('.svg', '');
        
        let exportName = prompt("Filename:", currentFileName + "_render");
        if(!exportName) return;

        draw(false);
        let u32 = new Uint32Array(window.u32);
        const k = [1, 4, 6, 4, 1], sum = 16;

        const blur = (data, horiz) => {
            const out = new Uint32Array(data.length);
            for(let y=0; y<HEIGHT; y++) {
                for(let x=0; x<WIDTH; x++) {
                    let r=0, g=0, b=0, a=0;
                    for(let i=-2; i<=2; i++) {
                        const idx = horiz ? y*WIDTH + Math.min(WIDTH-1, Math.max(0, x+i)) : Math.min(HEIGHT-1, Math.max(0, y+i))*WIDTH + x;
                        const c = data[idx];
                        r += (c & 0xff)*k[i+2]; g += ((c>>8)&0xff)*k[i+2]; b += ((c>>16)&0xff)*k[i+2]; a += ((c>>24)&0xff)*k[i+2];
                    }
                    out[y*WIDTH+x] = ((a/sum)<<24) | ((b/sum)<<16) | ((g/sum)<<8) | (r/sum);
                }
            }
            return out;
        };

        u32 = blur(u32, true); u32 = blur(u32, false);

        const tmp = document.createElement('canvas'); tmp.width = WIDTH; tmp.height = HEIGHT;
        tmp.getContext('2d').putImageData(new ImageData(new Uint8ClampedArray(u32.buffer), WIDTH, HEIGHT), 0, 0);
        
        const disp = document.createElement('canvas'); disp.width = DISPLAY; disp.height = DISPLAY;
        disp.getContext('2d').drawImage(tmp, 0, 0, WIDTH, HEIGHT, 0, 0, DISPLAY, DISPLAY);
        
        const dataURL = disp.toDataURL("image/png");
        document.getElementById('finalImg').src = dataURL;
        
        const link = document.getElementById('downloadLink');
        link.href = dataURL; link.download = exportName + ".png";
        document.getElementById('finalizedDiv').style.display = "block";
        draw(true);
    });

    // Boot
    start();
</script>
</body>
</html>
