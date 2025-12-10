<div align="center" style="font-family: system-ui, -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif; line-height: 1.6;">

  <h1 style="margin-bottom: 0.2em;">C++ Plotting Playground</h1>
  <p style="font-size: 0.95rem; max-width: 720px; margin: 0 auto;">
    A minimal, extensible C++17 project showcasing plotting with
    <strong>Matplot++ (matplotplusplus)</strong>, starting with
    <strong>line plots</strong> and <strong>histograms</strong> using
    <code>line.cpp</code> and <code>histogram.cpp</code>.
    Future extensions will include additional plot types such as pie charts and more.
  </p>

  <p style="font-size: 0.85rem; color: #666; margin-top: 0.5em;">
    Built with g++, MSYS2, CMake, Matplot++, and Gnuplot.
  </p>

</div>

<hr />

<!-- ========================================================= -->
<!-- Table of Contents                                        -->
<!-- ========================================================= -->

<ul style="list-style: none; padding-left: 0; font-size: 0.95rem;">
  <li>• <a href="#about-this-repository">About this repository</a></li>
  <li>• <a href="#matplotplusplus-and-gnuplot">Matplot++ and Gnuplot</a></li>
  <li>• <a href="#toolchain-gpp-and-msys2">Toolchain: g++ and MSYS2</a></li>
  <li>• <a href="#building-the-project">Building the project</a></li>
  <li>• <a href="#running-the-examples">Running the examples</a></li>
  <li>• <a href="#line-plots-module-linecpp">Line plots module (<code>line.cpp</code>)</a></li>
  <li>• <a href="#histogram-plots-module-histogramcpp">Histogram plots module (<code>histogram.cpp</code>)</a></li>
  <li>• <a href="#implementation-tutorial-video">Implementation tutorial video</a></li>
</ul>

---

## About this repository

This repository is a small but extensible playground for plotting in C++17 using the
<a href="https://github.com/alandefreitas/matplotplusplus" target="_blank">Matplot++</a> library.

Current examples:

- `line.cpp` — multiple line-plot demonstrations (multi-series plots, subplots, tiled layouts, markers, etc.).
- `histogram.cpp` — various histogram use-cases (different binning algorithms, normalization modes, categorical histograms, overlays, etc.).


---

## Matplot++ and Gnuplot

### What is Matplot++?

Matplot++ (also referred to as matplotplusplus) is a C++ graphics library inspired by MATLAB-style plotting.
It provides:

- Familiar plot functions like `plot`, `hist`, `fplot`, `subplot`, `tiledlayout`, etc.
- Support for multiple figure windows and subplots.
- Integration with Gnuplot for rendering.

This repository uses Matplot++ as a **header-only** dependency via a local clone.

### Installing Matplot++ (local to the repo)

You only need to do this once per clone of the repo.

1. Open **Git Bash** in the folder where `line.cpp` exists (i.e., the root of this project).
2. Clone Matplot++ into the `external` directory:

   ```bash
   git clone https://github.com/alandefreitas/matplotplusplus.git external/matplotplusplus/source
   ```

3. Ensure the include path `external/matplotplusplus/source` exists. The example build commands in this README rely on this path.

### Installing Gnuplot globally (MSYS2 / MinGW-w64)

Matplot++ uses Gnuplot as a backend renderer, so you must have Gnuplot installed and visible in your environment.

1. Open **MSYS2 MinGW 64-bit** shell  
   (important: **not** Windows `cmd` and **not** Git Bash).
2. Install Gnuplot with `pacman`:

   ```bash
   pacman -S mingw-w64-x86_64-gnuplot
   ```

3. Verify installation:

   ```bash
   gnuplot --version
   ```

If the version prints correctly, Gnuplot is installed and available globally in your MSYS2 MinGW 64-bit environment.

---

## Toolchain: g++ and MSYS2

On Windows, this project assumes you are using **MSYS2** and its MinGW-w64 toolchain.

### 1. Install MSYS2

- Download and install MSYS2 from its official site.
- After installation, open **MSYS2 MinGW 64-bit** (not the plain MSYS shell).

### 2. Update MSYS2 and core packages

In the MSYS2 MinGW 64-bit shell:

```bash
pacman -Syu
# You might need to close and reopen the shell after a full update.
```

### 3. Install g++ (MinGW-w64)

In the same MSYS2 MinGW 64-bit shell, install the C++ compiler:

```bash
pacman -S mingw-w64-x86_64-gcc
```

You can verify:

```bash
g++ --version
```

If this prints a version, your C++ toolchain is ready.

---

## Building the project

There are two primary ways described here:

1. A direct, single-file `g++` command (handy for quick testing).
2. A CMake-based build into a `build` directory.

### Option A: Quick single-file build (example)

From Git Bash or the MSYS2 MinGW 64-bit shell, in the project root (where `main.cpp` would exist):

```bash
g++ -std=c++17 main.cpp -Iexternal/matplotplusplus/source -o scatter_example
```

> Note: This is an example command. In this repository, you would typically build `line.cpp` or `histogram.cpp` via CMake as shown below, or adapt this pattern for manual compilation.

### Option B: CMake out-of-source build

The following steps assume a `CMakeLists.txt` is present and configured to build `line.cpp`, `histogram.cpp`, etc.

1. Open **Git Bash** in the directory where `line.cpp` exists (project root).
2. Remove any old build directory:

   ```bash
   rm -rf build
   ```

3. Create and enter a new `build` directory:

   ```bash
   mkdir build
   cd build
   ```

4. Generate the build system using MinGW Makefiles:

   ```bash
   cmake -G "MinGW Makefiles" ..
   ```

5. Build the project:

   ```bash
   cmake --build .
   ```

If everything is configured correctly, this will produce executables like:

- `line.exe`
- `histogram.exe`

inside the `build` directory.

---

## Running the examples

1. Open **Git Bash** in the folder where `line.cpp` exists (project root).
2. Navigate to the build directory:

   ```bash
   cd build
   ```

3. Run the line plot examples:

   ```bash
   ./line.exe
   ```

4. Run the histogram examples:

   ```bash
   ./histogram.exe
   ```

The figures will be displayed using Matplot++ and Gnuplot. Some histogram examples also save image files such as:

- `histogram_1.jpg`
- `histogram_2.svg`
- `histogram_3.png`
- `histogram_4.png`
- `histogram_5.jpg`
- `histogram_6.png`
- `histogram_7.jpg`

These will be created in your working directory (often `build/`).

---

<section id="line-plots-module-linecpp">

## Line plots module (`line.cpp`)

This section documents the **line plot** examples implemented in `line.cpp`.  
The section is designed to be **modular** so that you can reuse this structure for future plot types.

### Overview

`line.cpp` demonstrates:

- Multiple lines on a single set of axes.
- Plotting from containers like `std::set<std::vector<double>>`.
- Trigonometric functions with different styles and markers.
- Basic tiled layouts with `tiledlayout` and `nexttile`.
- Gridded subplots using `subplot` with various data and styles.

### Example set (high level)

- **Multiple line plots on the same axes**  
  Uses `linspace`, `transform`, multiple `plot` calls, and `hold(on)` to overlay:
  - `sin(x)`
  - `-sin(x)`
  - A linear function of `x`
  - A manually specified sequence of values

- **Plot from `std::set<std::vector<double>>`**  
  Demonstrates plotting a container of containers, where each `std::vector<double>` is plotted as its own series.

- **Sinusoidal functions with phase shifts**  
  Shows several `sin()` curves with different phase offsets in a single figure, with varying line styles.

- **Sinusoidal functions with markers**  
  Similar data to the previous example but uses different colors and markers to distinguish series.

- **Simple `tiledlayout` usage (2×1)**  
  Displays `sin(5x)` and `sin(15x)` stacked vertically using `tiledlayout(2, 1)` and `nexttile()` for explicit axes control.

- **3×2 subplot grid**  
  A more complex figure illustrating:
  - `sin(x)` with specific marker indices
  - `tan(sin(x)) - sin(tan(x))` with custom styling
  - `cos(5x)` with labeled axes and title
  - A "time plot" with custom tick labels (e.g., `"00:00s"`, `"01:00"`)
  - `sin(5x)` in a separate subplot
  - A circle drawn via parametric equations with `axis(equal)`

Use this section as a template if you later add modules like `pie.cpp`, `scatter.cpp`, etc.

</section>

---

<section id="histogram-plots-module-histogramcpp">

## Histogram plots module (`histogram.cpp`)

This section documents the **histogram** examples implemented in `histogram.cpp`.  
It is structured to be modular so additional histogram-related examples can be added easily.

### Overview

`histogram.cpp` demonstrates:

- Basic 1D histograms of normally distributed data.
- Different automatic binning algorithms.
- Changing the number of bins dynamically.
- Custom bin edges and different normalization modes.
- Categorical (string) histograms.
- Overlaid histograms for comparison.
- Histograms overlaid with theoretical probability density functions (PDFs).

### Example set (high level)

- **Simple histogram with automatic binning**  
  Uses `randn(10000, 0, 1)` to generate normal data and calls `hist(x)` for a basic histogram.  
  Shows how to:
  - Inspect bin count with `num_bins()`
  - Set labels and title
  - Resize the figure with `gcf()->size(...)`
  - Save to an image file (e.g., `histogram_1.jpg`)

- **Comparing binning algorithms**  
  Creates a `2×3` subplot grid to compare:
  - `automatic`
  - `scott`
  - `fd` (Freedman–Diaconis)
  - `integers`
  - `sturges`
  - `sqrt`  
  Useful for understanding how different rules change bin sizes and counts.

- **Dynamically changing the number of bins**  
  Demonstrates how to:
  - Retrieve the current number of bins
  - Update the title with `num2str(...)`
  - Change the number of bins at runtime using `h->num_bins(new_value)`
  - Optionally pause between updates using `std::this_thread::sleep_for(...)`

- **Custom bin edges & count-density normalization**  
  Shows how to:
  - Provide explicit bin edges as a `std::vector<double>`
  - Use `normalization::count_density` for normalized histograms
  - Save the result to, for example, `histogram_4.png`

- **Categorical (string) histogram**  
  Demonstrates histograms for text categories (e.g., `"yes"`, `"no"`, `"undecided"`).  
  Uses:
  - `hist(std::vector<std::string>)`
  - `bar_width(...)` to adjust bar width  
  Essentially acts as a bar chart for discrete string labels.

- **Overlaid normalized histograms**  
  Generates two normal distributions (e.g., different means or sample sizes), then:
  - Plots both on the same axes with `hold(on)`
  - Uses `normalization::probability`
  - Sets a common `bin_width` so comparisons are meaningful
  - Saves the figure (e.g., `histogram_6.png`)

- **Histogram with theoretical normal PDF overlay**  
  Demonstrates:
  - `normalization::pdf` so the histogram approximates a PDF
  - Computing a theoretical normal PDF with mean `mu` and standard deviation `sigma`
  - Using `fplot` to overlay a smooth theoretical curve on top of the histogram
  - Saving the figure (e.g., `histogram_7.jpg`)

As with the line module, you can replicate this pattern for future histogram-related or distribution-plot examples.

</section>

---

## Implementation tutorial video

At the end of the workflow, you can watch the full implementation and walkthrough on YouTube.


<a href="https://www.youtube.com/watch?v=YOUR_VIDEO_ID_HERE" target="_blank">
  <img
    src="https://img.youtube.com/vi/YOUR_VIDEO_ID_HERE/maxresdefault.jpg"
    alt="C++ Plotting with Matplot++ - Implementation Tutorial"
    style="max-width: 100%; border-radius: 8px; box-shadow: 0 4px 16px rgba(0,0,0,0.15); margin-top: 0.5rem;"
  />
</a>
