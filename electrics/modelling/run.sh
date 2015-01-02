#/bin/sh
refdes_renum --pgskip ./shceme.sch
gnetlist -g spice-sdb -o ./netlist.net ./scheme.sch
ngspice -b netlist.net -r result.txt