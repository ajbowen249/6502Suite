# Apple I Web Emulator

Another Apple I Emulator like the other one in the repository, but built to run on the web via [Emscripten](https://kripken.github.io/emscripten-site/index.html).

## Building
For sake of convenience (since it cross-compiles), this builds a little differently than the rest of the project. There are `clean` and `build` scripts here for doing exactly what you'd expect. `run` will serve up the main html file via `emrun`.

_Note: Build scripts have so far only been tested on Windows via the Git bash. In theory, they should build on any platform set up with Emscripten._
