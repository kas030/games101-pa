# GAMES101 PA

Personal PA repo for UCSB GAMES101 course.

## PA1: Rotation and Projection

The left image shows the original triangle without model rotation. The right
image shows the triangle after a 20-degree rotation around the z-axis.

<div style="display: flex; gap: 12px; align-items: flex-start;">
  <img src="./results/pa1-1.png" alt="Triangle without rotation" style="width: 49%;" />
  <img src="./results/pa1-2.png" alt="Triangle rotated by 20 degrees" style="width: 49%;" />
</div>

## PA2: Triangles and Z-buffering

The left image uses ordinary single-sample triangle rasterization. The right
image uses 2x2 MSAA to reduce jagged edges along the triangle boundaries.

<div style="display: flex; gap: 12px; align-items: flex-start;">
  <img src="./results/pa2-1.png" alt="Ordinary rasterization" style="width: 49%;" />
  <img src="./results/pa2-2.png" alt="Rasterization with 2x2 MSAA" style="width: 49%;" />
</div>
