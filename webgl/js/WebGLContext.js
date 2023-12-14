class WebGLContext {
  constructor(id) {
    let canvas = document.getElementById(id);
    if (!canvas) {
      throw new Error(
        `Unable to retrieve canvas element with id ${id}! Are you sure it's in the document and the DOM is loaded?`
      );
    }

    this.gl = canvas.getContext("webgl");
    if (!this.gl) {
      throw new Error(
        `Unable to retrieve WebGL context for canvas with id ${id}!`
      );
    }

    this.clearContext();
  }

  clearContext() {
    // Grayish blue clear color
    this.gl.clearColor(100.0 / 255.0, 132.0 / 255.0, 164.0 / 255.0, 1.0);
    this.gl.clear(this.gl.COLOR_BUFFER_BIT);
  }
}

export { WebGLContext };
