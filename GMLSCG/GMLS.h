﻿/*
2023-02-13
lot sizing cooperative game
*/

#pragma once

#include <fstream>
#include <string>
#include <sstream>

#include<vector>
#include <ilcplex/ilocplex.h>
using namespace std;

struct Parameter_Struct
{
	int i_index = -1;
	int t_index = -1;
	// int C = 0;

	int c_X = -1;
	int c_Y = -1;
	int c_I = -1;
	int d = -1;
	int s_X = -1;
	int s_Y = -1;
	int d_sum = -1;
};

// 初始解角标 it
struct Variabe_Struct
{
	int i_index = -1;
	int t_index = -1;
	int X = -1;
	int Y = -1;
	int I = -1;
};

struct All_Values
{
	int items_num = 3;
	int prids_num = 6; 
	int all_machs_num = 3;

	int current_iter = 0;
	float current_branch_var_value;

	int current_bench_time = 0;
	float current_optimal_bound=-1;

	int machine_capacity = 0;

	int core_find_flag = -1;
};

struct Coalition
{
	int index =-1;
	int cost = -1;
	vector<int> pattern;
};

struct All_Lists
{
	vector<Parameter_Struct> primal_parameters; // 物品时间角标
	vector<Variabe_Struct> current_solns_list; // 初始求解结果

	vector<int> MP_solns_list;

	vector<float>dual_prices_list;

	vector<vector<int>> X_fix;
	vector<vector<int>> Y_fix;
	vector<vector<int>> I_fix;

	vector<vector<int>> all_machine_demand;

	vector<int> single_machine_demand;

	vector<int> coalition_cost_list; // list of all possible c(S)
	
	vector<vector<int>> pattern_list;
	vector<int> pattern_idx_list;
	vector<int> pattern_cost_list;

	vector<int> SP_solns_list; // results of master problem

	vector<vector<int>> model_matrix; // master problem matrix modeled by rows 
	vector<vector<int>> Master_Matrix_C; // master problem matrix modeled by cols
	vector<vector<int>> demand_matrix;

	vector<Coalition> coalitions_list;
};


void FirstReadData(All_Values& Values, All_Lists& Lists,int coalition_flag);

void NewReadData(All_Values& Values, All_Lists& Lists, int coalition_flag);

void SolveOriginalProblem(All_Values& Values, All_Lists& Lists, int coalition_flag);

void ColumnGeneration(All_Values& Values, All_Lists& Lists);

void SolveFirstMasterProblem(
	All_Values& Values,
	All_Lists& Lists,
	IloEnv& Env_MP,
	IloModel& Model_MP,
	IloObjective& Obj_MP,
	IloRangeArray& Cons_MP,
	IloNumVarArray& Vars_MP,
	IloNumVarArray& V_Vars);

void SolveSubProblem(All_Values& Values, All_Lists& Lists);

void SolveUpdateMasterProblem(
	All_Values& Values,
	All_Lists& Lists,
	IloEnv& Env_MP,
	IloModel& Model_MP,
	IloObjective& Obj_MP,
	IloRangeArray& Cons_MP,
	IloNumVarArray& Vars_MP,
	IloNumVarArray& V_Vars);



#pragma once
