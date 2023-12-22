import { StringUtil } from "./util/StringUtil";
import flatVertexShader from "../../shaders/FlatShader.vert.glsl";
import flatFragmentShader from "../../shaders/FlatShader.frag.glsl";
import { Vertex3 } from "./Vertex3";
import { Triangle } from "./Triangle";

export class WebGLEngine {
  constructor(id) {
    let canvas = document.getElementById(id);

    // The width and height (in CSS pixels)
    this.width = canvas.clientWidth;
    this.height = canvas.clientHeight;

    // The "scene" (which is just a triangle for now).
    // By default, WebGL has a world coordinate system ranging (-1.0, 1.0) in all three directions,
    // with origin at (0.0, 0.0, 0.0);
    this.scene = new Triangle([
      new Vertex3(-1.0, -1.0, 0.0),
      new Vertex3(1.0, -1.0, 0.0),
      new Vertex3(1.0, 1.0, 0.0),
    ]);

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

    this.setupShaders(flatVertexShader, flatFragmentShader);
    this.scene.setupBuffers(this.gl);
  }

  setupShaders(vertexShaderSource, fragmentShaderSource) {
    // A vertex and fragment shader are required. All other shaders are
    // optional.
    this.vertexShader = this.addShader("vertex", vertexShaderSource);
    this.fragmentShader = this.addShader("fragment", fragmentShaderSource);

    this.linkShaders([this.vertexShader, this.fragmentShader]);
  }

  addShader(type, sourceCode) {
    let shaderTypeName = StringUtil.toTitleCase(type);

    let shaderType = null;
    switch (type) {
      case "vertex":
        shaderType = this.gl.VERTEX_SHADER;
        break;
      case "fragment":
        shaderType = this.gl.FRAGMENT_SHADER;
        break;
    }

    const shader = this.gl.createShader(shaderType);
    this.gl.shaderSource(shader, sourceCode);
    this.gl.compileShader(shader);
    if (!this.gl.getShaderParameter(shader, this.gl.COMPILE_STATUS)) {
      const errorLog = this.gl.getShaderInfoLog(shader);
      throw new Error(
        `${shaderTypeName} shader compilation failed due to an error: ${errorLog}`
      );
    }

    console.log(`${shaderTypeName} shader loaded!`);
    return shader;
  }

  linkShaders(shaders) {
    this.shaderProgram = this.gl.createProgram();
    for (let i = 0; i < shaders.length; i++) {
      this.gl.attachShader(this.shaderProgram, shaders[i]);
    }
    this.gl.linkProgram(this.shaderProgram);
    if (!this.gl.getProgramParameter(this.shaderProgram, this.gl.LINK_STATUS)) {
      let errorLog = this.gl.getProgramInfoLog(this.shaderProgram);
      throw Error(`Linking of shader programs failed due to: ${errorLog}`);
    }

    console.log("Shaders linked!");
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

    // Enable the shader program that we've already linked and prepared.
    this.gl.useProgram(this.shaderProgram);

    this.scene.draw(this.gl, this.shaderProgram);

    // We continue rendering by refreshing the frame and calling this.draw() when the next frame will be
    // rendered.
    window.requestAnimationFrame((ts) => {
      this.draw(ts);
    });
  }
}
