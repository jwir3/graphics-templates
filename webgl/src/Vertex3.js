/**
 * A vertex, or point, in 3 dimensions. It must have a position, but
 * can have color and normal data associated with it, as well.
 */
export class Vertex3 {
  constructor(x, y, z) {
    this.x = x;
    this.y = y;
    this.z = z;
  }

  addColor(red, green, blue, alpha) {
    this.r = red;
    this.g = green;
    this.b = blue;
    this.a = alpha;
  }
}
