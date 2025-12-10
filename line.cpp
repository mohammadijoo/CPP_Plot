#include <cmath>
#include <vector>
#include <set>
#include <matplot/matplot.h>

int main() {
    using namespace matplot;

    // 1) Multiple line plots on same axes
    {
        std::vector<double> x = linspace(0, 2 * pi);
        std::vector<double> y = transform(x, [](auto v) { return sin(v); });

        figure();
        plot(x, y, "-o");
        hold(on);
        plot(x, transform(y, [](auto v) { return -v; }), "--xr");
        plot(x, transform(x, [](auto v) { return v / pi - 1.; }), "-:gs");
        plot({1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1.0}, "k");
        xlabel("x");
        ylabel("y");
        title("Multiple line plots");
    }

    // 2) Plot from set of vectors
    {
        std::set<std::vector<double>> Y = {
            {16, 5, 9, 4},
            {2, 11, 7, 14},
            {3, 10, 6, 15},
            {13, 8, 12, 1}};

        figure();
        plot(Y);
        xlabel("x");
        ylabel("y");
        title("Multiple line plots (set of vectors)");
    }

    // 3) Sin function line plots
    {
        figure();
        std::vector<double> x = linspace(0, 2 * pi);
        std::vector<double> y1 = transform(x, [](auto v) { return sin(v); });
        std::vector<double> y2 =
            transform(x, [](auto v) { return sin(v - 0.25); });
        std::vector<double> y3 =
            transform(x, [](auto v) { return sin(v - 0.5); });

        plot(x, y1, x, y2, "--", x, y3, ":");
        xlabel("x");
        ylabel("y");
        title("Sin() function line plots");
    }

    // 4) Sin function line plots with markers
    {
        std::vector<double> x = linspace(0, 2 * pi);
        std::vector<double> y1 = transform(x, [](auto v) { return sin(v); });
        std::vector<double> y2 =
            transform(x, [](auto v) { return sin(v - 0.25); });
        std::vector<double> y3 =
            transform(x, [](auto v) { return sin(v - 0.5); });

        figure();
        plot(x, y1, "g", x, y2, "b--o", x, y3, "c*");
        xlabel("x");
        ylabel("y");
        title("Sin() function line plots with markers");
    }

    // 5) Simple tiledlayout example (separate figure)
    {
        std::vector<double> x = linspace(0, 3);
        std::vector<double> y1 = transform(x, [](auto v) { return sin(5 * v); });
        std::vector<double> y2 =
            transform(x, [](auto v) { return sin(15 * v); });

        figure();
        tiledlayout(2, 1);

        auto ax1 = nexttile();
        plot(ax1, x, y1);
        title(ax1, "Top Plot");
        ylabel(ax1, "sin(5x)");

        auto ax2 = nexttile();
        plot(ax2, x, y2);
        title(ax2, "Bottom Plot");
        ylabel(ax2, "sin(15x)");
    }

    // 6) Last figure: 3x2 subplots in a SINGLE block, 6 subplots total
    {
        figure();

        // Subplot (row 0, col 0): sin(x) with marker indices
        std::vector<double> x_a = linspace(0, 10);
        std::vector<double> y_a = transform(x_a, [](auto v) { return sin(v); });
        subplot(3, 2, 0);
        plot(x_a, y_a, "-o")
            ->marker_indices({0,  5,  10, 15, 20, 25, 30, 35, 40, 45,
                              50, 55, 60, 65, 70, 75, 80, 85, 90, 95});

        // Subplot (row 0, col 1): tan(sin(x)) - sin(tan(x))
        std::vector<double> x_b = linspace(-pi, +pi, 20);
        std::set<double> x2_b(x_b.begin(), x_b.end());
        std::vector<double> y_b =
            transform(x_b, [](auto v) { return tan(sin(v)) - sin(tan(v)); });
        subplot(3, 2, 1);
        plot(x2_b, y_b, "--gs")
            ->line_width(2)
            .marker_size(10)
            .marker_color("b")
            .marker_face_color({.5, .5, .5});

        // Subplot (row 1, col 0): cos(5x)
        std::vector<double> x_c = linspace(0, 10, 150);
        std::vector<double> y_c =
            transform(x_c, [](auto v) { return cos(5 * v); });
        subplot(3, 2, 2);
        plot(x_c, y_c)->color({0.f, 0.7f, 0.9f});
        title("2-D Line Plot");
        xlabel("x");
        ylabel("cos(5x)");

        // Subplot (row 1, col 1): time plot
        std::vector<double> x_d = linspace(0, 180, 7);
        std::vector<double> y_d = {0.8, 0.9, 0.1, 0.9, 0.6, 0.1, 0.3};
        subplot(3, 2, 3);
        plot(x_d, y_d);
        title("Time Plot");
        xlabel("Time");
        yrange({0, 1});
        xticks({0, 30, 60, 90, 120, 150, 180});
        xticklabels(
            {"00:00s", "30:00", "01:00", "01:30", "02:00", "02:30", "03:00"});

        // Subplot (row 2, col 0): sin(5x)
        std::vector<double> x_e = linspace(0, 3);
        std::vector<double> y_e =
            transform(x_e, [](auto v) { return sin(5 * v); });
        subplot(3, 2, 4);
        plot(x_e, y_e);
        title("sin(5x)");
        xlabel("x");
        ylabel("y");

        // Subplot (row 2, col 1): circle
        double r_f = 2.0;
        double xc_f = 4.0;
        double yc_f = 3.0;
        std::vector<double> theta_f = linspace(0, 2 * pi);
        std::vector<double> x_f =
            transform(theta_f, [=](auto t) { return r_f * cos(t) + xc_f; });
        std::vector<double> y_f =
            transform(theta_f, [=](auto t) { return r_f * sin(t) + yc_f; });
        subplot(3, 2, 5);
        plot(x_f, y_f);
        axis(equal);
    }

    show();
    return 0;
}
