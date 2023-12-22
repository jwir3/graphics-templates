export class Triangle {
  constructor(points, shaderProgram) {
    if (points.length !== 3) {
      throw new Error(`Triangle can only be initialized with three points.`);
    }

    this.positions = [];
    points.forEach((nextVertex) => {
      this.positions.push(nextVertex.x);
      this.positions.push(nextVertex.y);
      this.positions.push(nextVertex.z);
    });

    this.indices = [0, 1, 2];

    this.shaderProgram = shaderProgram;
  }

  getIndices() {
    return this.indices;
  }

  getPositions() {
    return this.positions;
  }

  setupBuffers(gl) {
    // Create a buffer object for the vertex data
    this.vertexBuffer = gl.createBuffer();

    // Bind a buffer to this buffer object
    gl.bindBuffer(gl.ARRAY_BUFFER, this.vertexBuffer);

    // Upload the data to the buffer
    const vertices = this.getPositions();
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

    // Now that we're done with the operation, we want to unbind the buffer so
    // we don't accidentally write to it again.
    gl.bindBuffer(gl.ARRAY_BUFFER, null);

    // Create a new buffer object to hold the index data.
    this.indexBuffer = gl.createBuffer();

    // Bind a buffer to this buffer object
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indexBuffer);

    // Upload the index data to the new buffer
    const indices = this.getIndices();
    gl.bufferData(
      gl.ELEMENT_ARRAY_BUFFER,
      new Uint16Array(indices),
      gl.STATIC_DRAW
    );

    // Again, unbind the buffer to prevent accidental mutation
    gl.bindBuffer(gl.ARRAY_BUFFER, null);
  }

  draw(gl) {
    // Enable the shader program that we've already linked, prepared
    // and added as part of this object.
    gl.useProgram(this.shaderProgram);

    gl.bindBuffer(gl.ARRAY_BUFFER, this.vertexBuffer);
    gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.indexBuffer);

    let position = gl.getAttribLocation(this.shaderProgram, "position");

    // Tell WebGL what the data in the buffer(s) actually represents, using a
    // vertex array object.
    gl.vertexAttribPointer(position, 3, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(position);

    // Draw the elements (triangles) in the scene.
    gl.drawElements(
      gl.TRIANGLES,
      this.getIndices().length,
      gl.UNSIGNED_SHORT,
      0
    );
  }

  getBuffers() {
    return {
      positionBuffer: this.vertexBuffer,
      indexBuffer: this.indexBuffer,
    };
  }
}
