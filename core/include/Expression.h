/*
* MIT License

* Copyright (c) 2025 Denis Klintukhov

* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/


#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <memory>
#include <boost/json.hpp>

namespace Core
{
    enum class Operation
    {
        Add,
        Sub,
        Mul,
        Div
    };

    class Expression
    {
    public:
        virtual boost::json::object ToJson() const = 0;
        virtual double Evaluate() const = 0;
        virtual ~Expression() = default;
    };

    class Constant final : public Expression
    {
    public:
        Constant(double value);
        boost::json::object ToJson() const override;
        double Evaluate() const override;

    private:
        double m_value;
    };

    class BinaryExpression final : public Expression
    {
    public:
        BinaryExpression(
            std::unique_ptr<Expression> left,
            std::unique_ptr<Expression> right,
            Operation op
        );

        boost::json::object ToJson() const override;
        double Evaluate() const override;

    private:
        Operation m_op;
        std::unique_ptr<Expression> m_left;
        std::unique_ptr<Expression> m_right;
    };
}

#endif
