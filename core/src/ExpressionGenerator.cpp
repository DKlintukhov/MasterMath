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


#include "pch.h"

#include <random>
#include "ExpressionGenerator.h"

namespace Core
{
    ExpressionGenerator::ExpressionGenerator(Config conf)
        : m_config{ conf }
        , m_generator{ std::random_device{}() }
        , m_intDist(conf.min, conf.max)
        , m_floatDist(0.0, 1.0)
    {
        m_ops.reserve(4);
        if (m_config.useAdd) m_ops.push_back(Operation::Add);
        if (m_config.useSub) m_ops.push_back(Operation::Sub);
        if (m_config.useMul) m_ops.push_back(Operation::Mul);
        if (m_config.useDiv) m_ops.push_back(Operation::Div);
    }

    std::unique_ptr<Expression> ExpressionGenerator::GenerateExpression()
    {
        return std::make_unique<BinaryExpression>(GenerateBinaryExpression());
    }

    BinaryExpression ExpressionGenerator::GenerateBinaryExpression()
    {
        Operation op = GenerateOperation();
        Constant a = GenerateConstant();
        Constant b = GenerateConstant();

        if (op == Operation::Sub)
        {
            return NormalizeSubBinaryExpression(a, b);
        }

        if (op == Operation::Div)
        {
            return NormalizeDivBinaryExpression(a, b);
        }

        return BinaryExpression(std::make_unique<Constant>(a), std::make_unique<Constant>(b), op);
    }

    BinaryExpression ExpressionGenerator::NormalizeSubBinaryExpression(Constant a, Constant b)
    {
        if (a.Evaluate() < b.Evaluate())
        {
            return BinaryExpression(std::make_unique<Constant>(b), std::make_unique<Constant>(a), Operation::Sub);
        }

        return BinaryExpression(std::make_unique<Constant>(a), std::make_unique<Constant>(b), Operation::Sub);
    }

    BinaryExpression ExpressionGenerator::NormalizeDivBinaryExpression(Constant a, Constant b)
    {
        double aVal = a.Evaluate();
        double bVal = b.Evaluate();

        if (aVal < bVal) {
            std::swap(aVal, bVal);
            std::swap(a, b);
        }

        if (bVal == 0.0)
        {
            if (aVal == 0.0)
            {
                return BinaryExpression(std::make_unique<Constant>(0.0), std::make_unique<Constant>(static_cast<double>(m_config.max)), Operation::Div);
            }
            else
            {
                return BinaryExpression(std::make_unique<Constant>(b), std::make_unique<Constant>(a), Operation::Div);
            }
        }

        double divisionResult = aVal / bVal;
        if (std::trunc(divisionResult) == divisionResult)
        {
            return BinaryExpression(std::make_unique<Constant>(a), std::make_unique<Constant>(b), Operation::Div);
        }

        return BinaryExpression(std::make_unique<Constant>(Constant(aVal * bVal)), std::make_unique<Constant>(b), Operation::Div);
    }

    Constant ExpressionGenerator::GenerateConstant()
    {
        if (m_config.useFloats)
        {
            return m_floatDist(m_generator) * (m_config.max - m_config.min) + m_config.min;
        }

        return static_cast<double>(m_intDist(m_generator));
    }

    Operation ExpressionGenerator::GenerateOperation()
    {
        std::uniform_int_distribution<size_t> dist(0, m_ops.size() - 1);
        return m_ops[dist(m_generator)];
    }
}
