#include "rover.h"

// Jeśli komenda o nazwie name już istnieje, to program_command ją nadpisuje.
// W przeciwnym przypadku dodaje ją do mapy.
RoverBuilder &RoverBuilder::program_command(char name, const recipe_t &rec) {
    recipes[name] = rec;
    return *this;
}

RoverBuilder &RoverBuilder::add_sensor(std::unique_ptr<Sensor> sensor) {
    // Żeby zachować unikatowość unique_ptr, musimy użyć std::move
    sensors.push_back(std::move(sensor));
    return *this;
}

// Przenosimy sensory i komendy do budowanego przez nas Rovera. Jako że
// RoverBuilder jest zdefiniowany jako friend Rovera, możemy skorzystać
// z prywatnego konstruktora.
Rover RoverBuilder::build() {
    return {std::move(sensors), std::move(recipes)};
}

// Przechodzimy się po każdej komendzie i szukamy, czy jest zaprogramowana.
// Jeśli nie, to wychodzimy z funkcji (zachowując stopped jako prawdę).
// Dla każdej komendy po kolei wykonujemy wszystkie jej ruchy, a przed
// wkroczeniem na nowe pole sprawdzamy dla każdego sensora, czy jest bezpiecznie
void Rover::execute(const std::string &commands) {
    if (!landed)
        throw RoverDidNotLandYetException();
    stopped = true;
    for (char command: commands) {
        auto it = recipes.find(command);
        if (it == recipes.end())
            return;
        for (auto &exec: it->second) {
            State newState = exec->next_state(state);
            for (auto &sens: sensors)
                if (!sens->is_safe(newState.get_x(), newState.get_y()))
                    return;
            state = exec->next_state(state);
        }
    }
    stopped = false;
}

// Wylądowanie jest zawsze możliwe, ustawia stan i sprawia, że nie liczymy już
// łazika jako zatrzymanego.
void Rover::land(std::pair<coordinate_t, coordinate_t> coords, Direction dir) {
    stopped = false;
    landed = true;
    state = State(coords, dir);
}

std::ostream &operator<<(std::ostream &os, const Rover &rover) {
    if (!rover.landed)
        return os << "unknown";
    return os << rover.state << (rover.stopped ? " stopped" : "");
}
