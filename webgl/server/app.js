const express = require("express");
const path = require("path");

const app = express();
const port = 3000;

// Serve all files in the /dist directory from localhost on port 3000.
app.use(express.static(path.join(__dirname, "../dist")));

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});
