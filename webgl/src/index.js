// import { Mesh } from "./Mesh";
import { WebGLEngine } from "./WebGLEngine";
import packageJson from "../package.json";
import "./style/scss/index.scss";

document.body.onload = () => {
  console.log(
    `Graphics Template (WebGL Version ${packageJson.version}) was used to create this project`
  );
  console.log(
    "Find out more at https://www.github.com/jwir3/graphics-projector"
  );
  let engine = new WebGLEngine("webgl");
  engine.startRenderLoop();
};
