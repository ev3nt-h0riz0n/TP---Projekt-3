#include <pybind11/pybind11.h>
#include <matplot/matplot.h>
#include <cmath>
#include <vector>
#include <sndfile.h>

namespace py=pybind11;
const double PI = 3.14159265358979323846;

double add(int i, int j)
{
    return i+j;
}
int sinus(double f) {
    using namespace matplot;
    fplot([&f](double x) { return sin(f * x *(2*PI)); })->line_width(3);
    ylabel("Wychylenie");
    xlabel("Czas [s]");
    xlim({ -2, 2 });
    ylim({ -1, 1 });
    yticks({ -1, -0.87, -0.71, -0.5, 0, 0.5, 0.71, 0.87, 1 });
    xticks({ -2.00, -1.50, -1.00, -0.50, 0, 0.50, 1.00, 1.50, 2.00 });
    yticklabels({ "-1", "-v3/2", "-v2/2", "-1/2", "0", "1/2", "v2/2", "v3/2", "1" });
    title("Wykres sygnalu sinusoidalnego o zadanej czestotliwosci");
    grid(on);

    show();
    return 0;
}
int cosinus(double f)
{
    using namespace matplot;

    fplot([&f](double x) { return cos(f * x * (2*PI)); })->line_width(3);
    ylabel("Wychylenie");
    xlabel("Czas [s]");
    title("Wykres sygnalu cosinusoidalnego o zadanej czestotliwosci");
    xlim({ -2, 2 });
    ylim({ -1, 1 });
    yticks({ -1, -0.87, -0.71, -0.5, 0, 0.5, 0.71, 0.87, 1 });
    xticks({-2.00, -1.50, -1.00, -0.50, 0, 0.50, 1.00, 1.50, 2.00});
    yticklabels({ "-1", "-v3/2", "-v2/2", "-1/2", "0", "1/2", "v2/2", "v3/2", "1" });
    grid(on);

    show();
    return 0;
}
int piloksztaltny(double f)
{
    // Wzor na wykres piloksztaltny: 2.0 * (x * t - (0.5 + x * t))
    using namespace matplot;

    fplot([&f](double x) {return 2.0 * (x * f - std::floor(0.5 + x * f)); })->line_width(3);
    ylabel("Wychylenie");
    xlabel("Czas [s]");
    xlim({ -2, 2 });
    ylim({ -1, 1 });
    yticks({ -1, -0.75, -0.5, -0.25, 0, 0.25, 0.50, 0.75, 1});
    yticklabels({ "-1", "-0.75", "-0.5", "-0.25", "0", "0.25", "0.50", "0.75","1" });
    xticks({ -2.00, -1.50, -1.00, -0.50, 0, 0.50, 1.00, 1.50, 2.00 });
    title("Wykres sygnalu piloksztaltnego o zadanej czestotliwosci");
    grid(on);

    show();
    return 0;
}
// wsp - współczynnik wypełnienia sygnału prostokątnego
int prostokatny(double f, double wsp) {
    using namespace matplot;
    
    fplot([&f, &wsp](double x)
        {
            double faza = std::fmod(f * x, 1.0);
            if (faza < 0) faza += 1.0;
            return faza < wsp ? 1.0 : -1.0;
        })->line_width(3);
    xlim({ -2, 2 });
    ylim({ -1, 1 });
    yticks({ -1, -0.75, -0.5, -0.25, 0, 0.25, 0.50, 0.75, 1 });
    yticklabels({ "-1", "-0.75", "-0.5", "-0.25", "0", "0.25", "0.50", "0.75","1" });
    xticks({ -2.00, -1.50, -1.00, -0.50, 0, 0.50, 1.00, 1.50, 2.00 });
    ylabel("Wychylenie");
    xlabel("Czas [s]");
    title("Wykres sygnalu prostokatnego o zadanej czestotliwosci i wspolczynniku wypelnienia");
    grid(on);
 
    show();
    return 0;
}


void autokorelacja_wykres(const std::vector<double>& sygnal)
{
    //https://pl.wikipedia.org/wiki/Autokorelacja
    using namespace matplot;

    int n = sygnal.size();
    std::vector<double> autokorelacja(n, 0.0);
    double srednia = 0.0;
    double suma = 0.0;

    for (int i = 0; i < n; ++i) {
        srednia += sygnal[i];
    }
    srednia /= n;

    for (int czas = 0; czas < n; ++czas) {
        suma = 0.0;
        for (int i = 0; i < n - czas; ++i) {
            suma += (sygnal[i] - srednia) * (sygnal[i + czas] - srednia);
        }
        autokorelacja[czas] = suma / (n - czas);
    }

    plot(autokorelacja);
    xlabel("Czas (lag)");
    ylabel("Autokorelacja");
    title("Wykres autokorelacji zadanego sygnalu");
    show();
}

int wizualizuj(const std::string& plik, int n)
{
    using namespace matplot;
    if (n <= 0)
    {
        std::cout << "Wprowadzony zly parametr, n powinno nalezec do zbioru liczb naturalnych dodatnich." << std::endl;
        return 1;
    }

    SF_INFO sfinfo;
    SNDFILE* file = sf_open(plik.c_str(), SFM_READ, &sfinfo);
    if (!file) {
        std::cout << "Nie mozna otworzyc pliku dzwiekowego: " << plik << std::endl;
        return 1;
    }
    const int probki = sfinfo.frames;

    // Odpowiednie probkowanie
    int co_ktora_probka = n;
    std::vector<double> samples;
    samples.reserve(probki / co_ktora_probka);
    std::vector<double> wszystkie(probki);
    sf_read_double(file, wszystkie.data(), probki);
    for (int i = 0; i < probki; i += co_ktora_probka) {
        samples.push_back(wszystkie[i]);
    }
    sf_close(file);

    plot(samples);
    title("Wizualizacja sygnału .wav");
    xlabel("Czas");
    ylabel("Amplituda");
    show();
    autokorelacja_wykres(samples);

    return 0;
}


PYBIND11_MODULE(sygnaly, h)
{
    h.doc() = "Biblioteka do generowania roznego rodzaju sygnalow, w tym sin/cos/prostokatnych/piloksztaltnych, zadanych w pliku audio oraz do filtracji 1D i 2D";
    h.def("add", &add);
    h.def("sin", &sinus);
    h.def("cos", &cosinus);
    h.def("pilo", &piloksztaltny);
    h.def("prosto", &prostokatny);
    h.def("wizualizacja", &wizualizuj);
}