import "./Mesh.js";

function onInitialLoad(id) {
  let context = initContext(id);
  clearContext(context);
}

// export const name = "main";
import { WebGLContext } from "./WebGLContext.js";

document.body.onload = () => {
  let context = new WebGLContext("webgl");
};
