#!/bin/sh
cd `readlink -f \`dirname $0\``
touch header

#une ligne pour chaque include a dump, dans l'ordre:
cat base/include/AResource>> header
cat base/include/IManager.hpp >> header
#cat base/include/TemplateManager.hpp >> header
cat base/include/Manager.hpp >> header
cat game/include/Image.hpp >> header
#cat game/include/specifiques.hpp >> header
echo >> header
