class BaseStackQueue:
	# 데이터 추가
	def push(self, data):
		raise NotImplemented
	# 데이터 꺼내기
	def pop(self):
		raise NotImplemented
	def peek(self):
		raise NotImplemented
	# 비어있는지 체크
	def isEmpty(self):
		raise NotImplemented
	# 꽉 차있는지 체크
	def isFull(self):
		raise NotImplemented
	# 리스트 전체 출력
	def display(self):
		raise NotImplemented
		
class ListStack(BaseStackQueue):
	def __init__(self, max_length=128):
		self.items = []
		self.max_length = max_length
    
	def push(self, item):
		if self.isFull():
			raise Exception('Stack is full')
		self.items.append(item)
    
	def pop(self):
		if self.isEmpty():
			raise Exception('Stack is empty')
		return self.items.pop()
	
	def isEmpty(self):
		return self.items == []
  
	def isFull(self):
		return self.size() == self.max_length

	def peek(self):
		if self.isEmpty():
			raise Exception('Stack is empty')
		return self.items[-1]

	def size(self):
		return len(self.items)
	
	def display(self):
		for v in self.items:
			print(v,end=",")



