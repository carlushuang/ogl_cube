#include "application.hpp"

/* for mesa driver, if not start up properly
 * MESA_GL_VERSION_OVERRIDE=3.3 MESA_GLSL_VERSION_OVERRIDE=330 must set before run
 */
int main(int argc, char ** argv){
    Application ap;
    ap.start_main_loop();
}
