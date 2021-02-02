import re
import os


def create_dataset(root: str):
    pattern_url = re.compile(r'<url>(.*?)</url>', re.S)
    pattern_content = re.compile(r'<content>(.*?)</content>', re.S)
    contents_list = []
    classes_list = []
    # 查看新闻的种类共有多少以及每个种类有多少篇新闻
    for file in os.listdir(root):
        # 设置路径打开文件
        file_path = os.path.join(root, file)
        with open(file_path, 'r', encoding='gbk', errors='ignore') as f:
            text = f.read()
            urls = pattern_url.findall(text)
            contents = pattern_content.findall(text)
            for i in range(len(urls)):
                pattern_class = re.compile(r'http://(.*?).sohu.com', re.S)
                classes_list.append(pattern_class.findall(urls[i][0]))
                classes_list.append(contents[i])
    return classes_list, contents_list


if __name__ == '__main__':
    classes_list, contents_list = create_dataset('../resource/sohu/')
    print(classes_list)
    print(contents_list)
