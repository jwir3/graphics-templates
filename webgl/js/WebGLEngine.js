class WebGLEngine {
  constructor(id) {
    let canvas = document.getElementById(id);
    this.lastTimeStamp = performance.now();
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
  }

  clearContext() {
    // Grayish blue clear color
    this.gl.clearColor(100.0 / 255.0, 132.0 / 255.0, 164.0 / 255.0, 1.0);
    this.gl.clear(this.gl.COLOR_BUFFER_BIT);
  }

  startRenderLoop() {
    window.requestAnimationFrame((timestamp) => {
      this.draw(timestamp);
    });
  }

  draw(timestamp) {
    this.clearContext();

    window.requestAnimationFrame((ts) => {
      this.draw(ts);
    });
  }
}

export { WebGLEngine };
