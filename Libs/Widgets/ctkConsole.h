/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/
/*=========================================================================

   Program: ParaView
   Module:    $RCSfile$

   Copyright (c) 2005-2008 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2. 

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/

#ifndef __ctkConsole_h
#define __ctkConsole_h

// Qt includes
#include <QWidget>
#include <QTextCharFormat>
#include <QCompleter>

// CTK includes
#include "ctkWidgetsExport.h"

class ctkConsolePrivate;
class ctkConsoleCompleter;

/// QWidget that provides an interactive console - you can send text to the
/// console by calling printString() and receive user input by connecting to the
/// executeCommand() slot.
class CTK_WIDGETS_EXPORT ctkConsole : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QColor promptColor READ promptColor WRITE setPromptColor)
  Q_PROPERTY(QColor outputTextColor READ outputTextColor WRITE setOutputTextColor)
  Q_PROPERTY(QColor errorTextColor READ errorTextColor WRITE setErrorTextColor)
  Q_PROPERTY(QColor commandTextColor READ commandTextColor WRITE setCommandTextColor)
  Q_PROPERTY(QColor welcomeTextColor READ welcomeTextColor WRITE setWelcomeTextColor)
  Q_PROPERTY(QString ps1 READ ps1 WRITE setPs1)
  Q_PROPERTY(QString ps2 READ ps2 WRITE setPs2)
  
public:
  ctkConsole(QWidget* parentObject = 0);
  virtual ~ctkConsole();

  /// Returns the current formatting that will be used by printMessage()
  QTextCharFormat getFormat() const;
  
  /// Sets formatting that will be used by printMessage()
  void setFormat(const QTextCharFormat& Format);

  /// Set a completer for this console
  void setCompleter(ctkConsoleCompleter* completer);

  QColor promptColor()const;

  /// \sa promptColor()
  void setPromptColor(const QColor& newColor);

  QColor outputTextColor()const;

  /// \sa outputTextColor()
  void setOutputTextColor(const QColor& newColor);

  QColor errorTextColor()const;

  /// \sa errorTextColor()
  void setErrorTextColor(const QColor& newColor);

  QColor commandTextColor()const;

  /// \sa commandTextColor()
  void setCommandTextColor(const QColor& newColor);

  QColor welcomeTextColor()const;

  /// \sa welcomeTextColor()
  void setWelcomeTextColor(const QColor& newColor);

  /// Prints text on the console
  void printMessage(const QString& message, const QColor& color);

  /// Returns the string used as primary prompt
  virtual QString ps1() const;

  /// Set the string used as primary prompt
  virtual void setPs1(const QString& newPs1);

  /// Returns the string used as secondary prompt
  virtual QString ps2() const;

  /// Set the string used as secondary prompt
  virtual void setPs2(const QString& newPs2);

signals:

  /// This signal emitted before and after a command is executed
  void executing(bool);

public slots:

  /// Clears the contents of the console
  virtual void clear();

protected:

  /// Called whenever the user enters a command
  virtual void executeCommand(const QString& Command);

protected:
  ctkConsole(ctkConsolePrivate * pimpl, QWidget* parentObject);

  QScopedPointer<ctkConsolePrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(ctkConsole);
  Q_DISABLE_COPY(ctkConsole);
};

//-----------------------------------------------------------------------------
class CTK_WIDGETS_EXPORT ctkConsoleCompleter : public QCompleter
{
public:

  /// Update the completion model given a string.  The given string
  /// is the current console text between the cursor and the start of
  /// the line.
  virtual void updateCompletionModel(const QString& str) = 0;
};


#endif