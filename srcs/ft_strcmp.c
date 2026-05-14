int ft_strlen(char *str)
{
    int res;

    res = 0;
    while(str[res])
        res++;
    return (res);
}

int ft_strcmp(char *s1, char *s2)
{
    int n;
    int i;

    n = ft_strlen(s1);
    i = 0;
    while(i < n)
    {
        if(s1[i] != s2[i])
            return (1);
        i++;
    }
    return (0);
}