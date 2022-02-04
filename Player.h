#pragma once
class Player
{

public : 
	void	LineDeleteSuccess(int count);
	int		GetScore();

private : 
	// 퀘스트 목록
	// 
	// 경험치?
	// 
	// 아이템 리스트
	// 
	// 전적
	// 
	// 점수
	int					_score = 0;
};

