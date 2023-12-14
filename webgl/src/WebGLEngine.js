export class WebGLEngine {
  constructor(id) {
    let canvas = document.getElementById(id);

    // The width and height (in CSS pixels)
    this.width = canvas.clientWidth;
    this.height = canvas.clientHeight;

    console.log(
      `Creating a WebGLEngine with size: ${this.width}x${this.height}`
    );

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
    // First, we clear the background. This makes it so that nothing will be drawn in the view
    // except the background color. Everything will be drawn on top of this background color.
    this.clearContext();

    // Set up the viewport. This sets up the transformation from normalized device coordinates
    // to screen coordinates.
    this.gl.viewport(0, 0, this.width, this.height);

    // We continue rendering by refreshing the frame and calling this.draw() when the next frame will be
    // rendered.
    window.requestAnimationFrame((ts) => {
      this.draw(ts);
    });
  }
}
