import matplotlib.pyplot as plt
import pandas as pd

# filename = "dlib_result.txt"
filename = "my_result.txt"

df = pd.read_csv(filename, delimiter=";", header=None, names= ["x","y","res"])
df1 = df[df['res'] == 0]
df2 = df[df['res'] == 1]
df3 = df[df['res'] == 2]

plt.scatter(df1.x, df1.y, s=15, c='red', label='0')
plt.scatter(df2.x, df2.y, s=15, c='green', label='1')
plt.scatter(df3.x, df3.y, s=15, c='black', label='2')
plt.legend()

plt.show()
