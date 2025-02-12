#!/usr/bin/env python
import re
import sys
import os

from pprint import pprint

# the offsets dictionaries that will store offsets from SE to VR
offsets = dict()
se_offsets = list()
vr_offsets = list()

# use the offsets file, which is just a space-deliminated list of SE->VR offsets
with open("skyrim_se_to_vr_offsets.txt") as offsets_file:
    for line in offsets_file:
        if line.strip() == "":
            continue
        
        offset_pair = line.split(' ')
        se_offset = offset_pair[0].strip()
        vr_offset = offset_pair[1].strip()
        
        se_offsets.append(se_offset)
        vr_offsets.append(vr_offset)
        
        # print(f"{se_offset}->{vr_offset}")
        offsets[se_offset] = vr_offset

# collect a list of all files in the target directory
source_filenames = list()
directory = r'include\doticu_skylib'
for dirpath, dirnames, files in os.walk(directory):
    for file_name in files:
        source_filenames.append(f"{file_name}")
       
# for each file
for source_filename in source_filenames:
    print(f"*** {source_filename} ***")
    output = []
    changed = False
    with open(f'{directory}\\{source_filename}') as source_file:
        for line in source_file:
            line = line.rstrip()

            # match if a hex value is found
            match = re.search(r"0x[\dA-F]{8}", line)
            if match:
                found_offset = match.group()
                if str.strip(line)[0:2] == "//":
                    #print(f"Skipping commented out line: {str.strip(line)}")
                    pass
                elif found_offset in vr_offsets:
                    #print(f"{found_offset} is VR already: {str.strip(line)}")
                    output.append(line)
                elif found_offset in offsets.keys():
                    # found a hex value, and an offset pairing. Replace the value and write to output.
                    line = line.replace(found_offset, offsets[found_offset])
                    print(f"{found_offset}->{offsets[found_offset]}: {str.strip(line)}")
                    output.append(line)
                    changed = True
                else:
                    # Hex found, but no offset. Report out and write the original line to the output
                    print(f"No offset for '{found_offset}' in: {str.strip(line)}")
                    output.append(line)
            else:
                # no changes made, just write the original line to the output
                output.append(line)
                
    if changed:
        # if any changes were made, overwrite the original file
        with open(f'{directory}\\{source_filename}', 'w', newline='') as out_file:
            for line in output:
                out_file.write(line + "\r\n")

