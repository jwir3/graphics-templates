import "./Mesh.js";

function onInitialLoad(id) {
  let context = initContext(id);
  clearContext(context);
}

// export const name = "main";
import { WebGLEngine } from "./WebGLEngine.js";

document.body.onload = () => {
  let engine = new WebGLEngine("webgl");
  engine.startRenderLoop();
};
