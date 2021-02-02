from typing import List

class MaximumMatch:
    """正向最大匹配的中文分词器"""
    def __init__(self):
        self.window_size = 3  # 字典中最长词条的字符数

    def cut(self, text: str) -> List[str]:
        global piece
        result = []
        index = 0  # 前指针
        text_length = len(text)
        dictionary = {'研究', '研究生', '声明', '起源'}
        while text_length > index:
            for r_index in range(self.window_size+index, index, -1):  # 后指针
                piece = text[index: r_index]
                if piece in dictionary:
                    index = r_index - 1
                    break

            index = index + 1
            result.append(piece)
        return result


class ReverseMaximumMatch:
    """逆向最大匹配"""
    def __init__(self):
        self.window_size = 3

    def cut(self, text: str) -> List[str]:
        result = []
        right = len(text)  # 右指针
        dic = {'研究', '研究生', '生命', '命', '的', '起源'}
        global piece
        while right > 0:
            for left in range(right - self.window_size, right):  # 固定右指针，左指针逐渐右移
                piece = text[left: right]  # 切片
                if piece in dic:  # 当命中时
                    right = left + 1  # 命中更新
                    break
            right = right - 1  # 自然更新
            result.append(piece)
        result.reverse()
        return result


class BidirectionalMaximumMatch:
    """双向最大匹配"""
    def _count_single_char(self, world_list: List[str]):
        """
        统计单字成词的个数
        """
        return sum(1 for word in world_list if len(word) == 1)

    def cut(self, text: str):
        mm = MaximumMatch()
        rmm = ReverseMaximumMatch()
        f = mm.cut(text)
        b = rmm.cut(text)
        if len(f) < len(b):
            return f
        elif len(f) > len(b):
            return b
        else:
            return b if self._count_single_char(f) >= self._count_single_char(b) else f



if __name__ == '__main__':
    text = '研究生命的起源'
    mm_tokenizer = MaximumMatch()
    print(mm_tokenizer.cut(text))
    rmm_tokenizer = ReverseMaximumMatch()
    print(rmm_tokenizer.cut(text))
    bmm = BidirectionalMaximumMatch()
    print(bmm.cut(text))
