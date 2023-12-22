import { vec3 } from "gl-matrix";
import { OrthographicCamera } from "./OrthographicCamera";

/**
 * A "Scene" in three dimensions. A Scene is a collection of all the objects we want to
 * draw, as well as the necessary camera and viewing transformations.
 */
export class Scene {
  constructor(gl, camera) {
    this.objects = [];
    this.gl = gl;
    this.camera = camera;
    this.eyePoint = vec3.fromValues(0, 0, 10.0);
    this.lookAt = vec3.fromValues(0, 0, 0);
    this.upVector = vec3.fromValues(0, 1.0, 0);

    if (!this.camera) {
      this.camera = new OrthographicCamera(
        gl,
        -1.0,
        1.0,
        -1.0,
        1.0,
        -10.0,
        10.0,
        this.eyePoint,
        this.lookAt,
        this.upVector
      );
    }
  }

  addTriangle(triangle) {
    triangle.setScene(this);
    this.objects.push(triangle);
    this.setupBuffers(this.gl);
  }

  setupBuffers(gl) {
    this.objects.forEach((nextObj) => {
      nextObj.setupBuffers(gl);
    });
  }

  getCamera() {
    return this.camera;
  }

  draw(gl) {
    this.objects.forEach((nextObj) => {
      nextObj.draw(gl);
    });
  }
}
