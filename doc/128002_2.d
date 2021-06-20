format 224

classcanvas 128002 class_ref 128002 // Ant
  classdiagramsettings member_max_width 0 end
  xyz 770.845 482.641 2000
end
classcanvas 128130 class_ref 128386 // Coord
  classdiagramsettings member_max_width 0 end
  xyz 182.12 398.154 2006
end
classcanvas 128642 class_ref 128514 // AntHill
  classdiagramsettings member_max_width 0 end
  xyz 40.3374 180.178 2012
end
classcanvas 128898 class_ref 128642 // Cellule
  classdiagramsettings member_max_width 0 end
  xyz 60.3374 746.294 2018
end
classcanvas 129154 class_ref 128770 // Egg
  classdiagramsettings member_max_width 0 end
  xyz 778.539 1164.68 2006
end
classcanvas 129410 class_ref 128898 // Food
  classdiagramsettings member_max_width 0 end
  xyz 286.256 592 2000
end
classcanvas 129538 class_ref 129282 // Larva
  classdiagramsettings member_max_width 0 end
  xyz 504.081 1151.91 2006
end
classcanvas 129794 class_ref 129410 // Map
  classdiagramsettings member_max_width 0 end
  xyz 1200.56 932.937 2024
end
classcanvas 131586 class_ref 129666 // Scene
  classdiagramsettings member_max_width 0 end
  xyz 1409.84 1033.94 2030
end
classcanvas 131842 class_ref 129794 // Warrior
  classdiagramsettings member_max_width 0 end
  xyz 910.052 1165.19 3005
end
classcanvas 132226 class_ref 129922 // Obstacle
  classdiagramsettings member_max_width 0 end
  xyz 128.767 599.454 2030
end
classcanvas 132482 class_ref 130050 // Pheromone
  classdiagramsettings member_max_width 0 end
  xyz 391.912 595.195 2012
end
classcanvas 132610 class_ref 130178 // Queen
  classdiagramsettings member_max_width 0 end
  xyz 634.334 1153.25 2017
end
relationcanvas 128258 relation_ref 128258 // <directional composition>
  decenter_begin 68
  decenter_end 809
  from ref 128002 z 2007 to point 729.61 524.06
  line 134530 z 2007 to point 729.61 526.68
  line 134658 z 2007 to ref 128130
  role_a_pos 259 521 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128386 relation_ref 128386 // <directional composition>
  decenter_begin 119
  decenter_end 947
  from ref 128002 z 2007 stereotype "<<:map>>" xyz 486 556 2007 to ref 128130
  role_a_pos 260 541 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128514 relation_ref 128514 // <directional composition>
  decenter_begin 14
  decenter_end 739
  from ref 128002 z 2007 to point 689.21 491.83
  line 133890 z 2007 to point 689.21 514.96
  line 134018 z 2007 stereotype "<<:map>>" xyz 447 520 2007 to ref 128130
  role_a_pos 261 508 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 128770 relation_ref 128898 // <directional composition>
  geometry HV unfixed
  decenter_end 140
  from ref 128642 z 2013 to point 189 343
  line 133378 z 2013 stereotype "<<:map>>" xyz 166 370 2013 to ref 128130
  role_a_pos 202 260 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129026 relation_ref 128770 // <generalisation>
  from ref 128642 z 2019 to ref 128898
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129282 relation_ref 129154 // <generalisation>
  from ref 129154 z 2007 to ref 128002
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129666 relation_ref 129538 // <generalisation>
  geometry VHV unfixed
  from ref 129538 z 2007 to point 541.33 1126.68
  line 134786 z 2007 to point 824.06 1126.68
  line 134914 z 2007 to ref 128002
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 129922 relation_ref 129922 // <directional composition>
  decenter_begin 587
  decenter_end 50
  from ref 129794 z 2025 to point 1276.18 80.42
  line 133506 z 2025 to point 288.9 80.42
  line 133634 z 2025 to point 286.28 348.5
  line 139778 z 2025 to point 286.28 372.94
  line 133762 z 2025 to ref 128130
  role_a_pos 259 383 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130050 relation_ref 130050 // <directional composition>
  decenter_begin 462
  decenter_end 595
  from ref 129794 z 2025 to point 963.15 1048.5
  line 138754 z 2025 to point 963.15 401.93
  line 138882 z 2025 to point 609.41 401.93
  line 139010 z 2025 to point 609.41 489.21
  line 139138 z 2025 to ref 128130
  role_a_pos 260 484 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130178 relation_ref 130178 // <directional composition>
  decenter_begin 289
  decenter_end 449
  from ref 129794 z 2025 to point 1040.02 1005.17
  line 136962 z 2025 to point 1040.02 321.13
  line 137090 z 2025 to point 529.61 321.13
  line 137218 z 2025 to point 529.61 464.46
  line 137346 z 2025 to ref 128130
  role_a_pos 260 459 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130306 relation_ref 130306 // <directional composition>
  decenter_begin 100
  decenter_end 159
  from ref 129794 z 2025 to point 1213.65 160.22
  line 135042 z 2025 stereotype "<<:map>>" xyz 769 162 2025 to point 368.7 160.22
  line 135170 z 2025 to point 368.7 414.96
  line 135298 z 2025 to ref 128130
  role_a_pos 260 410 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130434 relation_ref 130434 // <directional composition>
  decenter_begin 35
  decenter_end 231
  from ref 129794 z 2025 to point 1162.84 940.02
  line 135426 z 2025 to point 1162.84 200.62
  line 135554 z 2025 stereotype "<<:map>>" xyz 764 202 2025 to point 409.41 200.62
  line 135682 z 2025 to point 409.41 426.68
  line 135810 z 2025 to ref 128130
  role_a_pos 260 423 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130562 relation_ref 130562 // <directional composition>
  decenter_begin 202
  decenter_end 375
  from ref 129794 z 2025 to point 1081.73 983.35
  line 136450 z 2025 to point 1081.73 281.73
  line 136578 z 2025 stereotype "<<:map>>" xyz 764 283 2025 to point 489.21 281.73
  line 136706 z 2025 to point 489.21 451.43
  line 136834 z 2025 to ref 128130
  role_a_pos 261 447 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130690 relation_ref 130690 // <directional composition>
  decenter_begin 541
  decenter_end 662
  from ref 129794 z 2025 to point 923.75 1068.7
  line 139266 z 2025 to point 923.75 441.33
  line 139394 z 2025 to point 649.81 441.33
  line 139522 z 2025 to point 649.81 501.93
  line 139650 z 2025 stereotype "<<:map>>" xyz 427 507 2025 to ref 128130
  role_a_pos 260 496 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130818 relation_ref 130818 // <directional composition>
  decenter_begin 333
  decenter_end 86
  from ref 129794 z 2025 to point 1243.95 120.82
  line 134146 z 2025 stereotype "<<:map>>" xyz 764 122 2025 to point 328.3 120.82
  line 134274 z 2025 to point 328.3 401.93
  line 134402 z 2025 to ref 128130
  role_a_pos 260 396 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 130946 relation_ref 130946 // <directional composition>
  decenter_begin 123
  decenter_end 305
  from ref 129794 z 2025 to point 1121.13 963.15
  line 135938 z 2025 to point 1121.13 241.33
  line 136066 z 2025 stereotype "<<:map>>" xyz 764 243 2025 to point 449.81 241.33
  line 136194 z 2025 to point 449.81 439.71
  line 136322 z 2025 to ref 128130
  role_a_pos 261 435 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131074 relation_ref 131074 // <directional composition>
  decenter_begin 370
  decenter_end 518
  from ref 129794 z 2025 to point 1003.55 1025.37
  line 137986 z 2025 to point 1003.55 361.53
  line 138114 z 2025 stereotype "<<:map>>" xyz 765 363 2025 to point 569.01 361.53
  line 138242 z 2025 to point 569.01 476.18
  line 138370 z 2025 to ref 128130
  role_a_pos 260 472 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131202 relation_ref 131202 // <directional composition>
  decenter_begin 819
  decenter_end 814
  from ref 129794 z 2025 to point 1306.48 40.02
  line 133122 z 2025 stereotype "<<:map>>" xyz 750 42 2025 to point 236.78 40.02
  line 133250 z 2025 to ref 128130
  role_a_pos 255 310 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131714 relation_ref 129794 // <unidirectional association>
  from ref 129794 z 2031 to ref 131586
  role_a_pos 1368 1039 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 131970 relation_ref 132098 // <generalisation>
  geometry VHV unfixed
  from ref 131842 z 3006 to point 964.46 1126.68
  line 137474 z 3006 to point 824.06 1126.68
  line 137602 z 3006 to ref 128002
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 132098 relation_ref 131330 // <unidirectional association>
  decenter_begin 962
  decenter_end 19
  from ref 129794 z 3006 stereotype "<<:map>>" xyz 1040 1240 3006 to ref 131842
  role_a_pos 1032 1157 3000 no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 132354 relation_ref 131458 // <generalisation>
  geometry VHV unfixed
  from ref 132226 z 2031 to point 160.22 704.86
  line 137730 z 2031 to point 86.28 704.86
  line 137858 z 2031 to ref 128898
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
relationcanvas 132738 relation_ref 131842 // <generalisation>
  geometry VHV unfixed
  from ref 132610 z 2018 to point 687.59 1126.68
  line 138498 z 2018 to point 824.06 1126.68
  line 138626 z 2018 to ref 128002
  no_role_a no_role_b
  no_multiplicity_a no_multiplicity_b
end
end
