import resolve from 'rollup-plugin-node-resolve';
import uglify from 'rollup-plugin-uglify';
import commonjs from 'rollup-plugin-commonjs';

export default {
  entry: 'lib/es6/src/snabbdomDemo.js',
  moduleName: 'bs-snabbdom',
  format: 'iife',
  plugins: [ resolve(), commonjs() ],
  dest: 'dist/main.bundle.js'
};
