#ifndef THEME_H
#define THEME_H

#include <QString>
#include <QColor>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QApplication>

/**
 * @brief Centralized Theme Engine for btOS.
 *
 * Implements an Obsidian / Minimalist iOS aesthetic:
 * - Deep matte obsidian surfaces (#0F1015)
 * - Elevated squircle cards (#181920) with hairline borders (#282A36)
 * - Subtle violet/iris accent (#8B5CF6) and crisp typography
 */
class Theme {
public:
    // ==========================================
    // 1. Color Palette Tokens (Obsidian Dark)
    // ==========================================
    static constexpr const char* ColorBackground     = "#0F1015"; // Deep obsidian base
    static constexpr const char* ColorSurface        = "#181920"; // Elevated matte card
    static constexpr const char* ColorSurfaceHover   = "#22232D"; // Card hover
    static constexpr const char* ColorSurfacePressed = "#14151A"; // Card pressed
    static constexpr const char* ColorBorder         = "#282A36"; // Hairline slate border
    static constexpr const char* ColorBorderActive   = "#454859"; // Highlighted border
    static constexpr const char* ColorTextPrimary    = "#F1F2F6"; // High-contrast crisp text
    static constexpr const char* ColorTextMuted      = "#7E8294"; // Obsidian muted metadata
    static constexpr const char* ColorAccent         = "#8B5CF6"; // Obsidian Iris Violet
    static constexpr const char* ColorAccentHover    = "#A78BFA"; // Soft Iris hover
    static constexpr const char* ColorDanger         = "#F87171"; // Soft danger coral

    // ==========================================
    // 2. Metrics & Dimensions
    // ==========================================
    static constexpr int RadiusSmall  = 8;   // Pills, badges, small inputs
    static constexpr int RadiusMedium = 14;  // App cards, buttons (iOS squircle feel)
    static constexpr int RadiusLarge  = 20;  // Large panels, sheet containers

    // ==========================================
    // 3. Core Engine Setup
    // ==========================================
    static void applyTheme(QApplication* app);
    static QString getMasterStyleSheet();

    // ==========================================
    // 4. Convenience Helpers (Call Constantly)
    // ==========================================
    static void markAsCard(QWidget* widget);
    static void markAsPrimary(QPushButton* button);
    static void markAsGhost(QPushButton* button);
    static void markAsDanger(QPushButton* button);
    static void markAsTitle(QLabel* label);
    static void markAsMuted(QLabel* label);

    static void refreshWidget(QWidget* widget);
};

#endif // THEME_H
