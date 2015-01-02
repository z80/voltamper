v 20130925 2
C 40000 40000 0 0 0 title-B.sym
C 43500 48000 1 0 0 spice-model-1.sym
{
T 43600 48700 5 10 0 1 0 0 1
device=model
T 43600 48600 5 10 1 1 0 0 1
refdes=A101
T 44800 48300 5 10 1 1 0 0 1
model-name=AD825
T 44000 48100 5 10 1 1 0 0 1
file=../models/ad825.cir
}
N 47500 47700 47500 49900 4
N 47500 46900 47500 44500 4
C 49100 46100 1 90 0 resistor-1.sym
{
T 48700 46400 5 10 0 0 90 0 1
device=RESISTOR
T 48800 46300 5 10 1 1 90 0 1
refdes=R101
T 49100 46100 5 10 1 1 0 0 1
value=1k
}
C 50100 46100 1 90 0 resistor-1.sym
{
T 49700 46400 5 10 0 0 90 0 1
device=RESISTOR
T 49800 46300 5 10 1 1 90 0 1
refdes=R102
T 50100 46100 5 10 1 1 0 0 1
value=1k
}
C 50200 44800 1 90 0 capacitor-1.sym
{
T 49500 45000 5 10 0 0 90 0 1
device=CAPACITOR
T 49700 45000 5 10 1 1 90 0 1
refdes=C101
T 49300 45000 5 10 0 0 90 0 1
symversion=0.1
T 50200 44800 5 10 1 1 0 0 1
value=10p
}
N 50000 46100 50000 45700 4
{
T 50100 45800 5 10 1 1 0 0 1
netname=Vc
}
N 49000 47300 49000 47000 4
N 50000 47300 50000 47000 4
{
T 50000 47300 5 10 1 1 0 0 1
netname=Vout
}
N 49000 44000 49000 46100 4
N 50000 44800 50000 44500 4
N 50000 44500 49000 44500 4
C 48900 43700 1 0 0 gnd-1.sym
N 47000 47100 45500 47100 4
N 45500 47100 45500 46000 4
C 45400 45700 1 0 0 gnd-1.sym
N 42500 46500 42500 47500 4
N 42500 43500 42500 45300 4
C 48000 49800 1 270 0 vdc-1.sym
{
T 48650 49100 5 10 1 1 270 0 1
refdes=V101
T 48850 49100 5 10 0 0 270 0 1
device=VOLTAGE_SOURCE
T 49050 49100 5 10 0 0 270 0 1
footprint=none
T 48450 49100 5 10 1 1 270 0 1
value=DC 12V
}
C 45700 43300 1 0 0 vdc-1.sym
{
T 46400 43950 5 10 1 1 0 0 1
refdes=V102
T 46400 44150 5 10 0 0 0 0 1
device=VOLTAGE_SOURCE
T 46400 44350 5 10 0 0 0 0 1
footprint=none
T 46400 43750 5 10 1 1 0 0 1
value=DC 12V
}
N 46000 44500 46000 45000 4
N 46000 45000 47500 45000 4
N 46000 43300 46000 42500 4
N 48000 49500 47500 49500 4
N 49200 49500 50000 49500 4
N 50000 49000 50000 49500 4
C 45900 42200 1 0 0 gnd-1.sym
C 49900 48700 1 0 0 gnd-1.sym
C 42400 43200 1 0 0 gnd-1.sym
C 42200 45300 1 0 0 vac-1.sym
{
T 42900 45950 5 10 1 1 0 0 1
refdes=V123
T 42900 46150 5 10 0 0 0 0 1
device=vac
T 42900 46350 5 10 0 0 0 0 1
footprint=none
T 42900 45750 5 10 1 1 0 0 1
value=dc 5V ac 1V
}
C 47000 46900 1 0 0 aop-spice-1.sym
{
T 48050 47050 5 8 0 0 0 0 1
device=AOP-Standard
T 47700 47700 5 10 1 1 0 0 1
refdes=U100
T 46900 46600 5 10 1 1 0 0 1
model-name=AD825
}
N 48000 47300 50000 47300 4
N 47000 47500 42500 47500 4
{
T 42500 47500 5 10 1 1 0 0 1
netname=Vin
}
