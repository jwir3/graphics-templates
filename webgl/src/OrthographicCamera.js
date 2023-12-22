import { mat4, vec3 } from "gl-matrix";

export class OrthographicCamera {
  constructor(
    gl,
    left,
    right,
    top,
    bottom,
    near,
    far,
    eyePoint,
    lookAt,
    upVector
  ) {
    this.eyePoint = eyePoint;
    if (!this.eyePoint) {
      this.eyePoint = vec3.fromValues(0, 0, -10.0);
    }

    this.lookAt = lookAt;
    if (!this.lookAt) {
      this.lookAt = vec3.fromValues(0, 0, 0);
    }

    this.upVector = upVector;
    if (!this.upVector) {
      this.upVector = vec3.fromValues(0, 1.0, 0);
    }

    this.createViewMatrix();
    this.createProjectionMatrix(left, right, top, bottom, near, far);
    this.createViewProjectionMatrix();
  }

  createViewMatrix() {
    this.viewMatrix = mat4.create();
    mat4.lookAt(this.viewMatrix, this.eyePoint, this.lookAt, this.upVector);
  }

  createProjectionMatrix(left, right, top, bottom, near, far) {
    this.projectionMatrix = mat4.create();
    mat4.ortho(this.projectionMatrix, left, right, top, bottom, near, far);
  }

  createViewProjectionMatrix() {
    this.viewProjectionMatrix = mat4.create();
    mat4.mul(
      this.viewProjectionMatrix,
      this.getProjectionMatrix(),
      this.getViewMatrix()
    );
    return this.viewProjectionMatrix;
  }

  getProjectionMatrix() {
    return this.projectionMatrix;
  }

  getViewMatrix() {
    return this.viewMatrix;
  }

  getViewProjectionMatrix() {
    return this.viewProjectionMatrix;
  }
}
