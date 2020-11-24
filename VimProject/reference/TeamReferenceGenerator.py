import os
directory_from  = os.environ['HOME'] + '/VimProject/templates'
directory_to    = os.environ['HOME'] + '/VimProject/reference' 
allowed_suffixes = ['.cpp', '.tex']

data = ''
data += open(directory_from + '/TeamReferenceHeader.tex').read() + '\n'
data += r'\begin{document}' + '\n'
data += r'\tableofcontents' + '\n'
data += r'\newpage' + '\n'
data += '\n\n'

for filename in os.listdir(directory_from):
    good = False
    for s in allowed_suffixes:
        if (filename.endswith(s)): 
            good = True
    if (good == False): continue
    data += r'\section{' + filename + '}' + '\n'
    data += r'\begin{lstlisting}' + '\n'
    data += open(os.path.join(directory_from, filename)).read() + '\n'
    data += r'\end{lstlisting}' + '\n\n\n'

data += r'\end{document}'




open(directory_to + '/document.tex', 'w').write(data)
