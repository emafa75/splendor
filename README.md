# Sujet de projet de programmation du S5

La page du sujet :

https://www.labri.fr/perso/renault/working/teaching/projets/2023-24-S5-Munificence.php

La page sur thor :

https://thor.enseirb-matmeca.fr/ruby/projects/pr103

## Compilation du projet

make [project] : créer l'executable ./project sans couleurs, le nombre de jetons et le nombre d'architectes par défaut
make test : nettoie les sources du projet et créer l'executable ./test et l'execute
make color : nettoie les sources du projet, créer  l'executable ./project avec des couleurs et les valeurs par défauts. Lance une partie avec le mode verbeux et les graines par défau.
make evaluator : créer l'executable d'évaluation des parties
make cli : créer l'executable ./cli pour lancer l'interface graphique (sans couleurs par défaut)
make color_cli : créer l'executable ./cli pour lancer l'interface graphique avec les couleurs

## Architecture du projet : 
.
├── build
├── cli_src
│   ├── board
│   │   ├── cli_board.c
│   │   └── cli_board.h
│   ├── builders
│   │   ├── cli_builders.c
│   │   └── cli_builders.h
│   ├── cli.c
│   ├── cli_tests.c
│   ├── cli_tests.h
│   ├── fireworks
│   │   ├── fireworks.c
│   │   └── fireworks.h
│   ├── game
│   │   ├── cli_results.c
│   │   ├── cli_results.h
│   │   ├── cli_turn.c
│   │   └── cli_turn.h
│   ├── guild
│   │   ├── cli_guild.c
│   │   └── cli_guild.h
│   ├── market
│   │   ├── cli_market.c
│   │   └── cli_market.h
│   ├── players
│   │   ├── cli_players.c
│   │   └── cli_players.h
│   ├── skills
│   │   ├── cli_skills.c
│   │   └── cli_skills.h
│   ├── token
│   │   ├── cli_token.c
│   │   └── cli_token.h
│   └── utils
│       ├── cli_set.c
│       ├── cli_set.h
│       ├── cli_utils.c
│       └── cli_utils.h
├── compile_flags.txt
├── conventions.md
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
│   ├── ressources
│   │   ├── ressources.c
│   │   └── ressources.h
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
│       ├── stack
│       │   ├── stack.c
│       │   └── stack.h
│       ├── utils.c
│       ├── utils.h
│       └── vectors
│           ├── vector2.c
│           └── vector2.h
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
