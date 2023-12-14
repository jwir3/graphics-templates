const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
  entry: "./src/index.js",
  mode: "development",
  plugins: [
    new HtmlWebpackPlugin({
      title: "Graphics Projector: An Easy Template for WebGL Projects",
      template: "./src/index.html",
    }),
  ],
  module: {
    rules: [
      {
        test: /\.s[ac]ss$/i,
        use: [
          // Creates `style` nodes from JS strings
          "style-loader",
          // Translates CSS into CommonJS
          "css-loader",
          // Compiles Sass to CSS
          "sass-loader",
        ],
      },
      {
        // Allow the importing of .glsl (GLSL shader files) as raw text
        test: /\.glsl$/i,
        use: "raw-loader",
      },
    ],
  },
  output: {
    filename: "[name].bundle.js",
    path: path.resolve(__dirname, "dist"),
    clean: true,
  },
};
