# Sujet de projet de programmation du S5

La page du sujet :

https://www.labri.fr/perso/renault/working/teaching/projets/2023-24-S5-Munificence.php

La page sur thor :

https://thor.enseirb-matmeca.fr/ruby/projects/pr103


Architecture du projet : 
.
├── evaluator_src
│   ├── evaluator.c
│   └── visualiaze.py
├── Makefile
├── old_makefile
├── output.out
├── README.md
├── src
│   ├── builder.h
│   ├── builders
│   │   ├── builder.c
│   │   ├── builder_constants.h
│   │   ├── guild.c
│   │   └── guild.h
│   ├── color.h
│   ├── display
│   │   ├── board_display.c
│   │   └── board_display.h
│   ├── game
│   │   ├── game.c
│   │   └── game.h
│   ├── players
│   │   ├── players.c
│   │   └── players.h
│   ├── project.c
│   ├── skills
│   │   ├── favors
│   │   │   ├── favors.c
│   │   │   └── favors.h
│   │   ├── skills_builders.c
│   │   ├── skills_builders.h
│   │   ├── skills.c
│   │   ├── skills.h
│   │   ├── skills_tokens.c
│   │   └── skills_tokens.h
│   ├── token.h
│   ├── tokens
│   │   ├── color.c
│   │   ├── color_second_header.h
│   │   ├── market.c
│   │   ├── market.h
│   │   ├── token.c
│   │   └── token_second_header.h
│   └── utils
│       ├── ansi_color.h
│       ├── can_buy.c
│       ├── can_buy.h
│       ├── permutation
│       │   ├── permutation.c
│       │   └── permutation.h
│       ├── queue
│       │   ├── queue.c
│       │   └── queue.h
│       ├── set
│       │   ├── set.c
│       │   └── set.h
│       └── stack
│           ├── stack.c
│           └── stack.h
└── tst
    ├── test_builders
    │   ├── test_builders.c
    │   └── test_builders.h
    ├── test.c
    ├── test_guild
    │   ├── test_guild.c
    │   └── test_guild.h
    ├── test_market
    │   ├── test_market.c
    │   └── test_market.h
    ├── test_players
    │   ├── test_players.c
    │   └── test_players.h
    ├── test_skills
    │   ├── test_skills.c
    │   └── test_skills.h
    ├── test_tokens
    │   ├── test_tokens.c
    │   └── test_tokens.h
    └── test_utils
        ├── test_can_buy.c
        └── test_can_buy.h
