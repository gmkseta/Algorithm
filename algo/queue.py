class BaseQueue:
# 데이터의 추가
    def enqueue(self, data):
        raise NotImplemented
    # 데이터의 꺼내오기
    def dequeue(self):
        raise NotImplemented
    # 비어있는지 확인
    def isEmpty(self):
        raise NotImplemented
    # 꽉 차있는지 확인
    def isFull(self):
        raise NotImplemented
    # 리스트 전체 출력
    def display(self):
        raise NotImplemented

class queue(BaseQueue):
    def __init__(self,max_length):
        self.items = []
        self.max_length = max_length

    def enqueue(self, item):
        if self.isFull():
            raise Exception("Queue is full")
        self.items.insert(0, item)

    def dequeue(self):
        if self.isEmpty():
            raise Exception("Queue is empty")
        return self.items.pop()

    def isEmpty(self):
        return self.items == []

    def isFull(self):
        return self.size() == self.max_length

    def size(self):
        return len(self.items)
        	
	def display(self):
		for v in self.items:
			print(v,end=",")



