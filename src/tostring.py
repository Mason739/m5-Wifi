with open("index.js", 'r') as f:
    for line in f:
        print ('s += "{}\\n";'.format(str(line.strip()).replace('"', '\\"')))
