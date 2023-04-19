#include <Novice.h>
#include <cassert>
#include <Vector3.h>
#include <Matrix4x4.h>

const char kWindowTitle[] = "MT3_00_03_LE2A_11_トヨダユウキ";

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

/// <summary>
/// 3次元ベクトルの要素表示をする関数
/// </summary>
/// <param name="x">横</param>
/// <param name="y">縦</param>
/// <param name="vector">表示するベクトル</param>
/// <param name="label">名前</param>
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x); // x
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.y); // y
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.z); // z
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

/// <summary>
/// 4x4行列の要素表示をする関数
/// </summary>
/// <param name="x">横</param>
/// <param name="y">縦</param>
/// <param name="matrix">表示する行列</param>
/// <param name="Name">名前</param>
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* Name) {

	Novice::ScreenPrintf(x, y, "%s", Name);

	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			// 要素描画
			Novice::ScreenPrintf(
				x + column * kColumnWidth,
				y + row * kRowHeight + kRowHeight,
				"%6.02f",
				matrix.m[row][column]
			);
		}
	}
}

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="translate">三次元ベクトル</param>
/// <returns>平行移動した後の行列</returns>
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {

	// 結果格納用
	Matrix4x4 result;

	// 生成処理
	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;
	result.m[3][3] = 1.0f;

	return result;

}

/// <summary>
/// 拡大縮小行列
/// </summary>
/// <param name="scale">三次元ベクトル</param>
/// <returns></returns>
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {

	// 結果格納用
	Matrix4x4 result;

	// 生成処理
	result.m[0][0] = scale.x;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;

}

/// <summary>
/// 行列を3次元ベクトルに変換する関数
/// </summary>
/// <param name="vector">3次元ベクトル</param>
/// <param name="matrix">行列</param>
/// <returns></returns>
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {

	// 結果格納用
	Vector3 result;
	
	// 生成処理
	result.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]) + (vector.z * matrix.m[2][0]) + (1.0f * matrix.m[3][0]);
	result.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]) + (vector.z * matrix.m[2][1]) + (1.0f * matrix.m[3][1]);
	result.z = (vector.x * matrix.m[0][2]) + (vector.y * matrix.m[1][2]) + (vector.z * matrix.m[2][2]) + (1.0f * matrix.m[3][2]);
	float w =  (vector.x * matrix.m[0][3]) + (vector.y * matrix.m[1][3]) + (vector.z * matrix.m[2][3]) + (1.0f * matrix.m[3][3]);

	assert(w != 0.0f);

	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	/// 変数宣言
	Vector3 translate = { 4.1f, 2.6f, 0.8f };
	Vector3 scale = { 1.5f, 5.2f, 7.3f };
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Vector3 point = { 2.3f, 3.8f, 1.4f };
	Matrix4x4 transformMatrix = {
		1.0f, 2.0f, 3.0f, 4.0f,
		3.0f, 1.0f, 1.0f, 2.0f,
		1.0f, 4.0f, 2.0f, 3.0f,
		2.0f, 2.0f, 1.0f, 3.0f
	};
	Vector3 transformed = Transform(point, transformMatrix);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, kRowHeight, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 + kRowHeight, scaleMatrix, "scaleMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
