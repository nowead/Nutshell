/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damin <damin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 21:28:16 by seonseo           #+#    #+#             */
/*   Updated: 2024/07/03 18:13:18 by damin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// built_in_cmd.c
int     ft_strcmp(const char *s1, const char *s2);

// export.c
int		exec_export(char **argv, char ***envp);
int		export_single_env_var(char *env_var, char ***envp);
size_t	get_key_len(char *env_var);
char	**search_env_var(const char *key, size_t len, char *envp[]);
int		export_new_env_var(char *new_env_var, char ***envp);

// unset.c
int		exec_unset(char **argv, char ***envp);
int		unset_single_env_var(char *env_key, char ***envp);

// cd.c
int     exec_cd(char **argv, char ***envp);
int     update_oldpwd(char ***envp, int oldpwd_index, int pwd_index);
int     update_pwd(char ***envp, int pwd_index);
int     cd_home(char **argv, char **envp);
#endif
