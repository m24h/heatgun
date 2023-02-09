setlocal EnableDelayedExpansion 

for %%f in (*.c) do sdcc --fsigned-char --nooverlay --opt-code-size --peep-file peephole.txt  --xram-size 1024  --iram-size 256 --code-size 15360  -c %%f

set sdcc_rels=
for %%f in (*.rel) do set sdcc_rels=!sdcc_rels! %%f
sdcc  --out-fmt-ihx -o heatgun.ihx  --xram-size 1024  --iram-size 256 --code-size 15360 "-Wl -m,-M" %sdcc_rels%
set sdcc_rels=

packihx heatgun.ihx >heatgun.hex

makebin -p heatgun.hex heatgun.bin

findstr /c:"(REL," heatgun.map

type heatgun.mem
