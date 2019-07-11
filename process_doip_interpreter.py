import argparse, yaml, os, glob, re
from mako.template import Template

def generate_doip_packets(basePath, files, packets):
    templates = []
    for file in files:
        templates.extend(glob.glob(os.path.join(basePath, "./auto_gen/src/", file)))
    for file in templates:
        context_packets = {}
        file_path = os.path.abspath(file)
        template = Template(filename=file_path)
        f_name = re.sub(r'.([a-z]+).tmpl$', '' + '.\\1', file_path)
        f_name = re.sub(r'/auto_gen/src', '/auto_gen/out', f_name)
        targetFile = open(f_name, "w")
        targetFile.write(template.render(
                s_packets = packets["packets"],
                context_packets = context_packets
                ))
        targetFile.close()


basePath = os.path.dirname(os.path.realpath(__file__))
with open(os.path.join(basePath, "./auto_gen/src/doip_packets.yml"), 'r') as packets:
    try:
        y_packets = yaml.load(packets)
        # generate doip packets class
        file_temp = ['doip_packets.h.tmpl', 'doip_packets.cpp.tmpl', 'doip_packets.js.tmpl']
        generate_doip_packets(basePath, file_temp, y_packets)
    except yaml.YAMLError as exc:
        print(exc)
