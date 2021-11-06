#include "App.h"

int main(void)
{
    App* app = App::getInstance();
    app->loop();

    return 0;
}
