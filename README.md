# Summary
A widget on generating DoIP/UDS Packet class structure source code, based on
input yaml description file

# Executation
$python process_doip_interpreter.py

will generate source code at auto_gen/out

# Template Src File Description
- auto_gen/src/doip_packets.yml:
DoIP/Uds packet description, based on ISO-13400 and ISO-14229
- auto_gen/src/doip_packets.cpp.tmpl
- auto_gen/src/doip_packets.h.tmpl
c++ code template
- auto_gen/src/doip_packets.js.tmpl
js code template
