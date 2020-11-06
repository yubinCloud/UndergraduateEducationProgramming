"""
芯片测试
"""
import random
from enum import Enum


class TestResult(Enum):
    TWO_BAD = 0
    ONE_GOOD = 1
    TWO_GOOD = 2


class Chip:
    cur_id = 0

    def __init__(self, quality=True):
        """
        初始化
        :param quality: 芯片的质量是好还是坏，True为好，False为坏
        """
        Chip.cur_id += 1
        self.id = Chip.cur_id
        self.quality = quality

    def report(self, other_chip):
        if self.quality is True or random.randint(0, 1) == 1:
            return other_chip.quality
        return not other_chip.quality

    def __repr__(self):
        return "chip({} {})".format(self.id, self.quality)


def test(chip1, chip2):
    """
    测试两个芯片
    :param chip1: 芯片1
    :param chip2: 芯片2
    :return: 测试结果，由枚举的TestResult表示
    """
    return TestResult(chip1.report(chip2) + chip2.report(chip1))


def chip_test(chips):
    size = len(chips)

    while size > 3:
        groups = [(chips[i], chips[size - 1 - i]) for i in range(size // 2)]  # 分组
        cur_chips = list()  # 本次淘汰后选出的芯片
        for i in range(size // 2):
            if test(*(groups[i])) == TestResult.TWO_GOOD:
                cur_chips.append(groups[i][random.randint(0, 1)])

        if size % 2 == 1:  # 表示分组时有轮空的芯片
            left_chip = chips[size // 2]
            approve = 0  # 对它报告的成功数
            for chip in chips:
                if chip.report(left_chip):
                    approve += 1
            if approve >= len(chips) // 2:
                cur_chips.append(left_chip)

        chips = cur_chips
        size = len(chips)
        print(chips)

    # base case
    if size == 3:
        res = test(chips[0], chips[1])
        if res == TestResult.ONE_GOOD:
            return chips[2]
        else:
            return chips[0]
    if size == 2 or size == 1:
        return chips[0]


if __name__ == "__main__":
    all_chip = [Chip(True), Chip(False), Chip(True), Chip(True), Chip(False), Chip(True), Chip(False),
             Chip(False), Chip(True), Chip(True), Chip(False)]
    print(chip_test(all_chip))