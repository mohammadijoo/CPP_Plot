#include <cmath>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <array>
#include <string>
#include <iostream>
#include <matplot/matplot.h>

int main() {
    using namespace matplot;

    // 1) Simple histogram of standard normal data with automatic binning
    {
        std::vector<double> x1 = randn(10000, 0, 1);

        auto h1 = hist(x1);
        std::cout << "Histogram with " << h1->num_bins() << " bins" << std::endl;
        xlabel("Value");
        ylabel("Frequency");
        title("Histogram of standard normal data");

        // Set figure size (width, height in pixels for raster outputs)
        gcf()->size(1200, 800);
        save("histogram_1.jpg");
    }

    // 2) Compare different automatic binning algorithms for histograms
    {
        std::vector<double> x2 = randn(10000, 0, 1);

        auto f1 = figure(true);
        f1->size(1600, 900); // e.g. 16:9 layout for 2x3 subplots

        subplot(2, 3, 0);
        hist(x2, histogram::binning_algorithm::automatic);
        xlabel("Value");
        ylabel("Frequency");
        title("Automatic binning");

        subplot(2, 3, 1);
        hist(x2, histogram::binning_algorithm::scott);
        xlabel("Value");
        ylabel("Frequency");
        title("Scott's rule");

        subplot(2, 3, 2);
        hist(x2, histogram::binning_algorithm::fd);
        xlabel("Value");
        ylabel("Frequency");
        title("Freedman-Diaconis rule");

        subplot(2, 3, 3);
        hist(x2, histogram::binning_algorithm::integers);
        xlabel("Value");
        ylabel("Frequency");
        title("Integers rule");

        subplot(2, 3, 4);
        hist(x2, histogram::binning_algorithm::sturges);
        xlabel("Value");
        ylabel("Frequency");
        title("Sturges' rule");

        subplot(2, 3, 5);
        hist(x2, histogram::binning_algorithm::sqrt);
        xlabel("Value");
        ylabel("Frequency");
        title("Square root rule");

        save("histogram_2.svg");
    }

    // 3) Demonstrate changing the number of bins dynamically for a histogram
    {
        std::vector<double> x3 = randn(1000, 0, 1);

        auto h2 = hist(x3);
        xlabel("Value");
        ylabel("Frequency");
        title(num2str(h2->num_bins()) + " bins");

        for (size_t i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            title(num2str(h2->num_bins()) + " bins");
        }

        h2->num_bins(50);
        title(num2str(h2->num_bins()) + " bins");

        gcf()->size(1200, 800);
        save("histogram_3.png");
    }

    // 4) Histogram using custom bin edges and count-density normalization
    {
        std::vector<double> x4 = randn(10000, 0, 1);

        std::vector<double> edges = {-10.0000, -2.0000, -1.7500, -1.5000, -1.2500,
                                     -1.0000,  -0.7500, -0.5000, -0.2500, 0,
                                     0.2500,   0.5000,  0.7500,  1.0000,  1.2500,
                                     1.5000,   1.7500,  2.0000,  10.0000};
        auto f2 = figure(true);
        f2->size(1600, 900); // e.g. 16:9 layout for a single large histogram

        auto h4 = hist(x4, edges);
        h4->normalization(histogram::normalization::count_density);
        xlabel("Value");
        ylabel("Count density");
        title("Histogram with custom bin edges");

        save("histogram_4.png");
    }

    // 5) Categorical histogram (bar chart) for discrete string categories
    {
        std::vector<std::string> categories = {
            "no", "no",  "yes",       "yes",       "yes", "no",  "no",
            "no", "no",  "undecided", "undecided", "yes", "no",  "no",
            "no", "yes", "no",        "yes",       "no",  "yes", "no",
            "no", "no",  "yes",       "yes",       "yes", "yes"};

        auto f3 = figure(true);
        f3->size(1600, 900); // e.g. 16:9 layout for a single large histogram

        auto h_cat = hist(categories);
        h_cat->bar_width(0.5);
        xlabel("Category");
        ylabel("Count");
        title("Histogram of categorical responses");

        save("histogram_5.jpg");
    }

        // 6) Overlay normalized histograms for two different normal distributions
    {
        // Start a fresh figure for example 6
        auto fig6 = figure(true);
        fig6->size(1200, 800);

        std::vector<double> x5 = randn(2000, 0, 1);
        std::vector<double> y5 = randn(5000, 1, 1);

        auto h3 = hist(x5);
        hold(on); // overlay next histogram on the same axes
        auto h4 = hist(y5);

        h3->normalization(histogram::normalization::probability);
        h3->bin_width(0.25);
        h4->normalization(histogram::normalization::probability);
        h4->bin_width(0.25);

        xlabel("Value");
        ylabel("Probability");
        title("Overlaid normalized histograms");

        save("histogram_6.png");

        // Reset hold so the next example starts clean
        hold(off);
    }

    // 7) Histogram normalized to PDF overlaid with theoretical normal distribution
    {
        // Start a fresh figure for example 7
        auto fig7 = figure(true);
        fig7->size(1200, 800);

        std::vector<double> x6 = randn(5000, 5, 2);

        auto h5 = hist(x6);
        h5->normalization(histogram::normalization::pdf);
        hold(on); // overlay the theoretical PDF curve

        double mu = 5.0;
        double sigma = 2.0;
        const double pi = std::acos(-1.0);

        auto normal_pdf = [&](double y) {
            return std::exp(-std::pow((y - mu), 2.) / (2. * std::pow(sigma, 2.))) /
                   (sigma * std::sqrt(2. * pi));
        };
        fplot(normal_pdf, std::array<double, 2>{-5.0, 15.0})->line_width(1.5);

        xlabel("Value");
        ylabel("Probability density");
        title("Histogram with theoretical normal PDF");

        save("histogram_7.jpg");

        // Reset hold (good hygiene)
        hold(off);
    }

	
    // show();

    return 0;
}
