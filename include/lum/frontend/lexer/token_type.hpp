namespace lum{
    enum class TokenType{
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
        Bang,
        BangEqual,
        Greater,
        GreaterEqual,
        Less,
        LessEqual,

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
        For,
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
