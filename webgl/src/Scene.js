/**
 * A "Scene" in three dimensions. A Scene is a collection of all the objects we want to
 * draw, as well as the necessary camera and viewing transformations.
 */
export class Scene {
  constructor(gl) {
    this.objects = [];
    this.gl = gl;
  }

  addTriangle(triangle) {
    this.objects.push(triangle);
    this.setupBuffers(this.gl);
  }

  setupBuffers(gl) {
    this.objects.forEach((nextObj) => {
      nextObj.setupBuffers(gl);
    });
  }

  draw(gl) {
    this.objects.forEach((nextObj) => {
      nextObj.draw(gl);
    });
  }
}
