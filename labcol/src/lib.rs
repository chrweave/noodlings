use wasm_bindgen::prelude::*;
use std::collections::BinaryHeap;
use std::cmp::Ordering;

#[derive(Copy, Clone, PartialEq)]
struct Node {
    dist: f32,
    idx: usize,
}

// Priority queue needs reverse ordering for Min-Heap
impl Eq for Node {}
impl Ord for Node {
    fn cmp(&self, other: &Self) -> Ordering {
        other.dist.partial_cmp(&self.dist).unwrap_or(Ordering::Equal)
    }
}
impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

// The Eikonal quadratic solver for true Euclidean distance
fn solve_eikonal(a: f32, b: f32) -> f32 {
    if a.is_infinite() { return b + 1.0; }
    if b.is_infinite() { return a + 1.0; }
    
    // If the difference is too steep, the wavefront is effectively 1D
    if (a - b).abs() >= 1.0 {
        return a.min(b) + 1.0;
    }
    
    // Solve the 2D quadratic equation for a diagonal Euclidean front
    (a + b + (2.0 - (a - b) * (a - b)).sqrt()) / 2.0
}

#[wasm_bindgen]
pub fn compute_fmm(width: usize, height: usize, wall_data: &[u8], seed_x: usize, seed_y: usize) -> Vec<u16> {
    let size = width * height;
    let mut dists = vec![f32::INFINITY; size];
    
    // State tracking: 0 = Unvisited, 1 = Tentative (Heap), 2 = Frozen
    let mut state = vec![0u8; size]; 
    let mut heap = BinaryHeap::new();

    // Ensure seed is within bounds
    let target_x = seed_x.min(width - 1);
    let target_y = seed_y.min(height - 1);
    let start_node = target_y * width + target_x;

    dists[start_node] = 0.0;
    state[start_node] = 1;
    heap.push(Node { dist: 0.0, idx: start_node });

    // Up, Down, Left, Right
    let dirs = [(0isize, -1isize), (0, 1), (-1, 0), (1, 0)];

    while let Some(Node { dist: _, idx }) = heap.pop() {
        // Lazy deletion safeguard: skip if already frozen
        if state[idx] == 2 { continue; }
        state[idx] = 2; // Mark as frozen

        let x = idx % width;
        let y = idx / width;

        for &(dx, dy) in &dirs {
            let nx = x as isize + dx;
            let ny = y as isize + dy;

            if nx >= 0 && nx < width as isize && ny >= 0 && ny < height as isize {
                let n_idx = (ny as usize) * width + (nx as usize);
                
                if wall_data[n_idx] == 0 { continue; } // It's a wall
                if state[n_idx] == 2 { continue; }     // Already frozen

                // Find minimum frozen horizontal neighbor
                let mut min_x = f32::INFINITY;
                if nx > 0 && state[n_idx - 1] == 2 { 
                    min_x = min_x.min(dists[n_idx - 1]); 
                }
                if nx < (width as isize) - 1 && state[n_idx + 1] == 2 { 
                    min_x = min_x.min(dists[n_idx + 1]); 
                }

                // Find minimum frozen vertical neighbor
                let mut min_y = f32::INFINITY;
                if ny > 0 && state[n_idx - width] == 2 { 
                    min_y = min_y.min(dists[n_idx - width]); 
                }
                if ny < (height as isize) - 1 && state[n_idx + width] == 2 { 
                    min_y = min_y.min(dists[n_idx + width]); 
                }

                let new_dist = solve_eikonal(min_x, min_y);

                if new_dist < dists[n_idx] {
                    dists[n_idx] = new_dist;
                    state[n_idx] = 1; // Mark as tentative
                    heap.push(Node { dist: new_dist, idx: n_idx });
                }
            }
        }
    }

    // Normalize strictly from frozen pixels
    let max_d = dists.iter().zip(state.iter())
        .filter(|&(_, &s)| s == 2)
        .map(|(&d, _)| d)
        .fold(0.0f32, f32::max);
    
    dists.into_iter().zip(state.into_iter()).map(|(d, s)| {
        if s == 2 { ((d / max_d) * 65535.0) as u16 } 
        else { 0 }
    }).collect()
}
