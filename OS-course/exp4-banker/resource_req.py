"""
表示一条资源请求
@Time: 2020/11/7 21:39
@Author:
@File: resource_req.py
"""

class BaseResourceRequest:
    """一个资源的请求"""
    def __init__(self, proc, nums):
        self.proc = proc
        self.nums = nums


class ApplyRequest(BaseResourceRequest):
    """一次申请资源的请求"""
    def __init__(self, proc, nums):
        super(ApplyRequest, self).__init__(proc, nums)


class ReleaseRequest(BaseResourceRequest):
    """一次释放资源的请求"""
    def __init__(self, proc, nums):
        super(ReleaseRequest, self).__init__(proc, nums)