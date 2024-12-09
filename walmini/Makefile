# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 18:08:56 by walhamad          #+#    #+#              #
#    Updated: 2024/09/04 18:08:57 by walhamad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
LIB			:= -Llibft -lft
# INCLUDE		:= -I./includes -I./libft/srcs -I/opt/homebrew/opt/readline/include
# READLINE	:= -L/opt/homebrew/opt/readline/lib -lreadline -I/opt/homebrew/opt/readline/include
INCLUDE 	:= -I./includes -I./libft/srcs -I$(HOME)/local/readline/include
READLINE 	:= -L$(HOME)/local/readline/lib -lreadline -lhistory -I$(HOME)/local/readline/include
CFLAGS		:= $(INCLUDE) -Wall -Wextra -Werror
NEWLINE 	= \e[1K\r

#------------------------COLORS------------------------#

DEF_COLOR	= \033[0;39m
GRAY		= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m
H_RED		= \033[0;101m
RESET		= \033[0m

#------------------------PATH--------------------------#

SRCS_PATH		:= src
OBJS_PATH		:= obj
BUILTINS_PATH	:= $(SRCS_PATH)/builtins
CORE_PATH		:= $(SRCS_PATH)/core
EXEC_PATH		:= $(SRCS_PATH)/executor
LEXER_PATH		:= $(SRCS_PATH)/lexer
PARSER_PATH		:= $(SRCS_PATH)/parser
REDIR_PATH		:= $(SRCS_PATH)/redirects
SIGNAL_PATH		:= $(SRCS_PATH)/signals
UTILS_PATH      := $(SRCS_PATH)/utils
LIBFT_PATH		:= libft

#------------------------FILES-------------------------#

BUILTINS	= cd echo env exit export pwd unset
CORE		= error_handler free_resources init_shell main prompt_handler
EXEC		= command_executor path_utils
LEXER		= expander lexer tokenizer
PARSER		= parser syntax_checker
REDIR		= heredoc_handler iofile_handler pipe_handler redirection_handler
SIGNAL		= signal_handler
UTILS       = env_utils string_utils utils builtin_utils handler_utils redir_utils redir_utils2 wildcard_handler executor_utils lexer_utils

#------------------------------------------------------#

SRCS		:= $(addsuffix .c, $(addprefix $(BUILTINS_PATH)/, $(BUILTINS)))
SRCS		+= $(addsuffix .c, $(addprefix $(CORE_PATH)/, $(CORE)))
SRCS		+= $(addsuffix .c, $(addprefix $(EXEC_PATH)/, $(EXEC)))
SRCS		+= $(addsuffix .c, $(addprefix $(LEXER_PATH)/, $(LEXER)))
SRCS		+= $(addsuffix .c, $(addprefix $(PARSER_PATH)/, $(PARSER)))
SRCS		+= $(addsuffix .c, $(addprefix $(REDIR_PATH)/, $(REDIR)))
SRCS		+= $(addsuffix .c, $(addprefix $(SIGNAL_PATH)/, $(SIGNAL)))
SRCS		+= $(addsuffix .c, $(addprefix $(UTILS_PATH)/, $(UTILS)))
OBJS		:= $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)

#------------------------------------------------------#

vpath %.c $(BUILTINS_PATH) $(CORE_PATH) $(EXEC_PATH) $(LEXER_PATH) $(PARSER_PATH) $(REDIR_PATH) $(SIGNAL_PATH) $(UTILS_PATH)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(NEWLINE)$(CYAN)Creating object file $@ from $<"

all: ${NAME}
${NAME}: ${OBJS}
	@printf "$(NEWLINE)$(RESET)\n"
	@make -C $(LIBFT_PATH)
	@${CC} ${CFLAGS} $^ ${READLINE} ${INCLUDE} ${LIB} -o $@
	@echo "$(GREEN)$(NAME) was created$(RESET)"

clean:
	@make fclean -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)
	@echo "$(BLUE)$(NAME): $(CYAN)object files are cleaned$(RESET)"

fclean: clean
	@rm -rf ${NAME}
	@echo "$(BLUE)$(NAME): $(H_RED) $(NAME) was deleted $(RESET)"

re: fclean all

.PHONY: all clean fclean re
