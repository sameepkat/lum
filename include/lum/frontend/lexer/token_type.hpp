namespace lum{
enum class TokenType {
  LeftParen,
  RightParen,
  LeftBrace,
  RightBrace,
  LeftBracket,
  RightBracket,
  Comma,
  Dot,
  Colon,

  // Operators
  Plus,
  Minus,
  Star,
  Slash,
  Percent,

  // Comparison
  Equal,
  EqualEqual,
  BangEqual,
  Greater,
  GreaterEqual,
  Less,
  LessEqual,

  // Logical
  LogicalOR,
  LogicalAND,
  LogicalNOT,

  // Pipeline
  Arrow, // ->

  // Literals
  Identifier,
  Number,
  String,

  // Keywords
  Fn,
  If,
  Else,
  While,
  Continue,
  Break,
	Return,
	True,
	False,
	Nil,

	// Special
	EndOfFile,
	Use,
	NewLine
};
}
