"""# 교차 검증과 그리드 서치"""

"""## 검증 세트"""

import pandas as pd

wine = pd.read_csv("https://bit.ly/wine_csv_data")

data = wine[["alcohol", "sugar", "pH"]]
target = wine["class"]

from sklearn.model_selection import train_test_split

train_input, test_input, train_target, test_target = train_test_split(
    data, target, test_size=0.2, random_state=42
)
sub_input, val_input, sub_target, val_target = train_test_split(
    train_input, train_target, test_size=0.2, random_state=42
)

print(sub_input.shape, val_input.shape)


from sklearn.tree import DecisionTreeClassifier

dt = DecisionTreeClassifier(random_state=42)
dt.fit(sub_input, sub_target)
print(dt.score(sub_input, sub_target))
print(dt.score(val_input, val_target))

"""## 교차 검증"""

from sklearn.model_selection import cross_validate
