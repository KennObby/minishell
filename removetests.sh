#!/bin/bash
rm -r "minishell_tester/"
make fclean >/dev/null 2>&1 || true
rm -r "$0"
